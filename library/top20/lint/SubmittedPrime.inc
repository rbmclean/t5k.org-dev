<?php

namespace Top20;

/**
 * Represents a *single* submitted prime, potentially part of a larger "batch" submission
 */
final class SubmittedPrime
{
    /** @var string[] $singleComment Each potentially valid comment on the prime */
    public readonly array $singleComment;

    /**
     * Turn raw strings into something usable by linters
     *
     * @param string $prime The prime - equal to the "description" field (in quotes if unparsable) *or* a prime_blob_###
     * @param string $comment Official comment
     */
    public function __construct(readonly public string $prime, readonly public string $comment)//TODO needs to handle "credit comments" like [BR12]
    {
        //populate singleComment, keeping parenthesis in mind
        $singleComment = array();
        $parenLevel = 0;
        $curVal = "";
        foreach (explode(",", $comment) as $value) {
            $curVal .= $value;
            $parenLevel += substr_count($value, "(") - substr_count($value, ")");
            if (!$parenLevel) {
                $singleComment[] = $curVal;
                $curVal = "";
            }
        }
        if ($curVal !== "") {
            //well, the comment is misformed
            //we still want to add this though, otherwise it could be interpreted as no comment
            $singleComment[] = $curVal;
        }
        $this->singleComment = $singleComment;
    }
}
