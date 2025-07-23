<?php

namespace Top20\Linters;

use PDO;
use Top20\Linters\BaseLinter;
use Top20\Category;
use Top20\LintResult;
use Top20\SubmittedPrime;

/**
 * Find Mersenne primes from description/comments
 */
final class Mersenne extends BaseLinter
{
    /**
     * @inheritDoc
     */
    public function lint(PDO $db, SubmittedPrime $prime, array $others = []): array
    {
        if (!preg_match("/^2\\^\\d+-1$/", $prime->prime)) {
            return [];
        }

        //I'm not going to bother trying to find the Mersenne # here
        //considering I doubt a non-admin would ever submit one due to size restrictions
        $finalComment = "Mersenne";
        foreach ($prime->singleComment as $comment) {
            //must start "Mersenne", then a number, optionally with 1 or 2 question marks
            if (preg_match("/^[Mm]ersenne \d+\??\??$/", $comment)) {
                $finalComment = $comment;
                break;
            }
        }
        //TODO existing Mersenne's have a "Mersenne" subcategory...
        return [new LintResult(Category::Mersenne, true, $finalComment)];
    }
}
