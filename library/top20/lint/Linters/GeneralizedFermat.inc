<?php

namespace Top20\Linters;

use PDO;
use Top20\Linters\BaseLinter;
use Top20\Category;
use Top20\LintResult;
use Top20\SubmittedPrime;

class GeneralizedFermat extends BaseLinter
{
    /**
     * @inheritDoc
     */
    public function lint(PDO $db, SubmittedPrime $prime, array $others = []): array
    {
        //there's some odd cases here - see https://github.com/t5kowner/t5k.org/issues/21
        //the safest way is to just see if the raw decimal form can be written as b^2+1
        //because the "true" definition is b^2^n+1, and that's the same as (b^(n/2))^2+1 - a GFN-1
        if (gmp_perfect_square(gmp_sub($prime->number->getExpansion(), 1))) {
            return [new LintResult(Category::GeneralizedFermat, true, "generalized Fermat")];
        }
        return [];
    }
}
