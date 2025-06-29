<?php

namespace Top20;

use PDO;

/**
 * Find Mersenne primes from description/comments
 */
final class Mersenne extends BaseLinter
{
    /**
     * @see BaseLinter::lint
     */
    public function lint(PDO $db, SubmittedPrime $prime, array $others = []): ?LintResult
    {
        if (!preg_match("/^2\\^\\d+-1$/", $prime->prime)) {
            return null;
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
        return new LintResult(Category::Mersenne, true, $finalComment); //TODO existing Mersenne's have a "Mersenne" subcategory...
    }
}
