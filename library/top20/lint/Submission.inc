<?php

namespace Top20;

use PDO;

/**
 * Represents an entire prime submission (primes/submit.php)
 */
final class Submission
{
    /**
     * @var SubmittedPrime[] $entries All primes submitted
     */
    public readonly array $entries;

    /**
     * Creates a Submission for linting purposes
     *
     * @param string $blob User's freetext blob
     **/
    public function __construct(string $blob)
    {
        $entries = array();
        foreach (explode("\n", trim($blob)) as $line) {
            $entries[] = new SubmittedPrime(strstr($line, " ", true) ?? $line, strstr($line, " ") ?? "");
        }
        $this->entries = $entries;
    }

    /**
     * Run linting on this submission
     *
     * @param PDO $db Database connection
     * @return ?LintResult[] The results from linting, if any
     **/
    public function lint(PDO $db): ?array
    {
        # code...
    }
}
