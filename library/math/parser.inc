<?php

namespace Math;

function getDecimalExpansion(string $desc): string
{
    //TODO rewrite parser...
    return shell_exec("/var/www/html/primes/support/math/parser -f " . escapeshellarg($desc) . "b");
}
