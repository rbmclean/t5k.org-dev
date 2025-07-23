<?php

namespace Top20\Linters;

use PDO;
use Top20\Linters\BaseLinter;
use Top20\Category;
use Top20\LintResult;
use Top20\SubmittedPrime;
use const Top20\ARCHIVABLE_COUNT;

class DividesSomething extends BaseLinter
{
    /**
     * @inheritDoc
     */
    public function lint(PDO $db, SubmittedPrime $prime, array $others = []): array
    {

        $results = [];
        foreach ($prime->singleComment as $comment) {
            //old behavior allowed reusing the initial "divides" comment for multiple tags
            //ex: Divides Fermat F(1234), GF(1234,12)
            //this doesn't work well - it lead to duplicate divisor comments slipping through the cracks and
            //links added to the comment

            //so, we'll move to requiring the "Divides" comment per dividend
            //to support the transition, we'll find comments with and without, and just add it
            //this can be removed once everything has been re-linted with the PHP implementation
            if (!str_starts_with(strtolower($comment), "divides ")) {
                $comment = "divides " . $comment;
            }

            if (preg_match("/^[Dd]ivides Fermat F\\(\\d+\\)$/", $comment)) {
                $results[] = new LintResult(Category::FermatDivisor, false, $comment);
                continue;
            }

            if (preg_match("/^[Dd]ivides GF\\(\\d+,(3|5|6|10|12)\\)$/", $comment, $matches)) {
                $results[] = new LintResult(
                    Category::GFDivisor,
                    false,
                    $comment,
                    "Divides GF(*,$matches[1])",
                    ARCHIVABLE_COUNT
                );
                continue;
            }

            //weird handling here seems to be because of https://t5k.org/primes/page.php?id=97516
            if (preg_match("/^[Dd]ivides Phi\\(\\d+\\^\\d+(|\\/\\d+|\\/\\d+\\^\\d+),\\d+\\)$/", $comment)) {
                $results[] = new LintResult(Category::DividesPhi, false, $comment);
            }
        }
        return $results;
    }
}
