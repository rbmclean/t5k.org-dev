<?php

namespace Top20\Linters;

use Math\Number;
use PDO;
use Top20\Linters\BaseLinter;
use Top20\Category;
use Top20\LintResult;
use Top20\SubmittedPrime;

use function Top20\doesNumberExist;

use const Top20\ARCHIVABLE_COUNT;

final class Twin extends BaseLinter
{
    /**
     * @inheritDoc
     */
    public function lint(PDO $db, SubmittedPrime $prime, array $others = []): array
    {
        //TODO rare case where a prime isn't initially submitted as a twin
        //but someone else comes along later and proves it is
        //how do we make sure the original prime gets comment + archival tag added appropriately?

        if (doesNumberExist($db, (new Number())->fromDescription($prime->number->getExpansion() . "+2"), $others)) {
            return [new LintResult(Category::Twin, true, "twin (p)", "Twin (p)", ARCHIVABLE_COUNT)];
        }
        if (doesNumberExist($db, (new Number())->fromDescription($prime->number->getExpansion() . "-2"), $others)) {
            return [new LintResult(Category::Twin, true, "twin (p+2)", "Twin (p+2)", ARCHIVABLE_COUNT)];
        }
        return [];
    }
}
