<?php

namespace Top20\Linters;

use PDO;
use Top20\Linters\BaseLinter;
use Top20\Category;
use Top20\LintResult;
use Top20\SubmittedPrime;

class GeneralizedRepunit extends BaseLinter
{
    /**
     * @inheritDoc
     */
    public function lint(PDO $db, SubmittedPrime $prime, array $others = []): array
    {
        //we allow Generalized Repunits if they can be written as (b^n-1)/(b-1)
        //with the restrictions b!=2 (these are Mersenne), b!=10 (this is a Repunit), b>0 (negative bases are weird),
        //n>=5 (everything works with n=2, making the list pointless,
        //n=3 is testable as n(n+1)+1, making n-1 tests easy which would fill the list,
        //and n=4 is never prime since 4 isn't prime)
        for ($b = gmp_init(3), $bPrev = gmp_init(2); ; $bPrev = $b, $b = gmp_add($b, 1)) {
            $bPow = gmp_add(gmp_mul($prime->number->getExpansion(), $bPrev), 1);
            //are we past n=5 being viable?
            if (gmp_cmp(gmp_root($bPow, 5), $b) < 1) {
                return [];
            }
            if (gmp_perfect_power($bPow)) {
                //we don't care what power this is - just that it's at least 5
                for ($n = 2; $n <= 4; $n++) {
                    $res = gmp_rootrem($bPow, $n);
                    if (!gmp_cmp($res[0], $b) && !gmp_cmp($res[1], 0)) {
                        continue 2;
                    }
                }
                //base 10 is special
                if (!gmp_cmp($b, 10)) {
                    return [new LintResult(Category::Repunit, true, "repunit")];
                }

                //we have something!
                return [new LintResult(Category::GeneralizedRepunit, true, "generalized repunit")];
            }
        }
    }
}
