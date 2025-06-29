<?php

namespace Top20;

use PDO;

abstract class BaseLinter
{
    /**
     * @var $linters array<string> All class names of linters, ready for construction
     */
    public static array $linters = []; //TODO better place for this?

    /**
     * Determines if/how a submission qualifies for a particular archival tag
     *
     *
     * @param PDO $db Database handle
     * @param SubmittedPrime $prime Prime to lint
     * @param array<SubmittedPrime> $others Other primes in this submission (ex: to check for existence of twin)
     * @return ?LintResult Info for archival tag if qualified, otherwise null
     **/
    abstract public function lint(PDO $db, SubmittedPrime $prime, array $others = []): ?LintResult;
}
