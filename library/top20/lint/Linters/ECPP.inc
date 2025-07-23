<?php

namespace Top20\Linters;

use PDO;
use Top20\Linters\BaseLinter;
use Top20\Category;
use Top20\LintResult;
use Top20\SubmittedPrime;

class ECPP extends BaseLinter
{
    /**
     * @inheritDoc
     */
    public function lint(PDO $db, SubmittedPrime $prime, array $others = []): array
    {
        if (array_search("ECPP", $prime->singleComment)) {
            return [new LintResult(Category::ECPP, false, "ECPP")];
        }
        return [];
    }
}
