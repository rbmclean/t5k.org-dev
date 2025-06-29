<?php

use Top20\BaseLinter;

require_once dirname(__FILE__) . "/Mersenne.inc";
BaseLinter::$linters[] = "\\Top20\\Mersenne";
