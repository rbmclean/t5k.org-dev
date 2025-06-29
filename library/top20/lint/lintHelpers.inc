<?php

namespace Top20;

use PDO;

/**
 * @param PDO $db Database handle
 * @param SubmittedPrime $prime prime to lint
 * @param array<SubmittedPrime> $others Other primes to test $prime against (ex: twin prime submission)
 * @return array<LintResult> archival tag info
 */
function lintAll(PDO $db, SubmittedPrime $prime, array $others = []): array
{
    $ret = [];
    foreach (BaseLinter::$linters as $linter) {
        /** @var $singleLinter  BaseLinter */
        $singleLinter = new $linter();
        $lintResult = $singleLinter->lint($db, $prime, $others);
        if ($lintResult) {
            $ret[] = $lintResult;
        }
    }
    return $ret;
}
