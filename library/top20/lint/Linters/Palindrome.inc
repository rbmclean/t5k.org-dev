<?php

namespace Top20\Linters;

use PDO;
use Top20\Category;
use Top20\Linters\BaseLinter;
use Top20\LintResult;
use Top20\SubmittedPrime;

class Palindrome extends BaseLinter
{
    /**
     * @inheritDoc
     */
    public function lint(PDO $db, SubmittedPrime $prime, array $others = []): array
    {
        if (strrev($prime->number->getExpansion()) == $prime->number->getExpansion()) {
            return [new LintResult(Category::Palindrome, true, "palindrome")];
        }
        return [];
    }
}
