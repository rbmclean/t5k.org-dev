<?php

namespace Top20\Linters;

use Math\Number;
use PDO;
use Top20\Category;
use Top20\LintResult;
use Top20\SubmittedPrime;

use function Top20\doesNumberExist;

class KTuplet extends BaseLinter
{
    private const NAMES = [
        3 => "triplet",
        4 => "quadruplet",
        5 => "quintuplet",
        6 => "sextuplet",
        7 => "septuplet",
    ];

    /**
     * @inheritDoc
     */
    public function lint(PDO $db, SubmittedPrime $prime, array $others = []): array
    {
        foreach ($prime->singleComment as $comment) {
            $k = 0;
            $n = 0;
            foreach (self::NAMES as $index => $name) {
                if (preg_match('/^' . $name . ' \((\d+)\)$/', $comment, $matches)) {
                    $k = $index;
                    $n = $matches[1];
                    break;
                }
            }
            if (preg_match('/^(\d+)-tuplet \((\d+)\)$/', $comment, $matches)) {
                $k = $matches[1];
                $n = $matches[2];
            }
            if ($k >= 3 && $n <= $k) {
                $d = $this->getDiameter($k);
                $minIndex = $n;
                $maxIndex = $n;
                $minDiff = 0;
                $maxDiff = 0;
                for ($diff = 2; $diff <= $d; $diff += 2) {
                    if (
                        $minIndex > 1 && doesNumberExist(
                            $db,
                            (new Number())->fromDescription("(" . $prime->prime . ")-" . $diff),
                            $others
                        )
                    ) {
                        $minIndex++;
                        $minDiff = $diff;
                    }
                    if (
                        $maxIndex < $k && doesNumberExist(
                            $db,
                            (new Number())->fromDescription("(" . $prime->prime . ")+" . $diff),
                            $others
                        )
                    ) {
                        $maxIndex++;
                        $maxDiff = $diff;
                    }
                }
                if ($minIndex == 1 && $maxIndex == $k && ($minDiff + $maxDiff == $d)) {
                    $comment = $k . "-tuplet";
                    if (isset(self::NAMES[$k])) {
                        $comment = self::NAMES[$k];
                    }
                    $comment .= "($n)";
                    return [new LintResult($this->getCategory($k), true, $comment, $comment)];
                }
            }
        }
        return [];
    }

    private function getCategory(int $k): Category
    {
        return match ($k) {
            3 => Category::Triplet,
            4 => Category::Quadruplet,
            5 => Category::Quintuplet,
            6 => Category::Sextuplet,
            7 => Category::Septuplet,
            default => Category::ktuplet,
        };
    }

    private function getDiameter(int $ktupleSize): int
    {
        //need all primes <= $ktupleSize
        $primesToCheck = [];
        for ($i = 2; $i <= $ktupleSize; $i++) {
            foreach ($primesToCheck as $prime) {
                if ($i % $prime == 0) {
                    continue 2;
                }
            }
            $primesToCheck[] = $i;
        }

        //now we need $ktupleSize numbers as close together as possible that don't have all residues for any prime above
        //we know the closest possible is >= ($ktupleSize * 2 + 2), so start there and keep trying until successful
        for ($size = ($ktupleSize * 2 + 2);; $size += 2) {
            $indexModifying = 1;
            $vals = [0];
            while (1) {
                if ($indexModifying == 0) {
                    //we've backtracked completely with no luck
                    break;
                }
                if (isset($vals[$indexModifying])) {
                    $vals[$indexModifying] += 2;
                } elseif ($indexModifying == $ktupleSize - 1) {
                    $vals[$indexModifying] = $size;
                } else {
                    $vals[$indexModifying] = $vals[$indexModifying - 1] + 2;
                }

                if ($vals[$indexModifying] > $size) {
                    //we're ending at something too big - backtrack
                    unset($vals[$indexModifying]);
                    $indexModifying--;
                    continue;
                }
                //if we added the last element, check if valid
                if ($indexModifying == $ktupleSize - 1) {
                    foreach ($primesToCheck as $prime) {
                        $modsSeen = [];
                        foreach ($vals as $val) {
                            $modsSeen[$val % $prime] = 1;
                            if (sizeof($modsSeen) >= $prime) {
                                //invalid
                                unset($vals[$indexModifying]);
                                $indexModifying--;
                                continue 3;
                            }
                        }
                    }
                }
                return $size;
            }
        }
    }
}
