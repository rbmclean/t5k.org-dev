<?php

namespace Top20;

use PDO;

/**
 * Represents how an archival tag should be created (static properties)
 */
final class LintResult
{
    /**
     * Creates a LintResult
     *
     * @param Category $category What kind of archival tag?
     * @param bool $verified Was this completely verified, or is additional work needed later? (ex: GF divisor)
     * @param string $officialComment What should be part of the official comment for this prime?
     * @param string $subcategory The subcategory for this tag (ex: length of AP)
     **/
    public function __construct(
        readonly public Category $category,
        readonly public bool     $verified,
        readonly public string   $officialComment,
        readonly public string   $subcategory = ""
    )
    {
    }

    public function onList(PDO $db, string $description): bool
    {
        //plan only implement active ones
        //get rid of tolerated/deprecated/unknown, including comments
        //TODO maybe add "legacy" flag for ones that *based on current criteria* wouldn't have made the list (isn't there a historical list?)
        //if there's a subcategory, it's an archivable class
        //if there's not, it just "archivable"
        //TODO what about "deprecated" and others? Can I remove them and just preserve the prime record somehow?
        //TODO actually clean up subcategories
        //TODO except twins - both (p) and (p+2) are in the same category

        //TODO delete archivable records (confirmed no primes would have been deleted without them)
        //after double checking deprecated vs tolerated vs unknown
        //66, 63,50,38,35,17
        //will also require removing that from comments
        //TODO decide about others that would mean primes should have never been on the list
        //60,59,58,52,51,46,36,34,33,22,32

        //TODO special "largest" archivable -  nothing has it, but we want the top 20 page (id 3)

        //TODO get rid of ECPP page? private note has no reasoning for it

        //instead of BaseLinter, just be "top 20 page"?

        //TODO make constants somewhere
        $threshold = empty($this->subcategory) ? 20 : 5;
        //TODO need to fix subcategories on non-archival classes/linters
        if (
            !$result = $db->query(
                "SELECT prime.log10, prime.description FROM archival_tag INNER JOIN prime ON archival_tag.prime_id=prime.id 
                 WHERE archival_tag.category_id=" . $this->category->value . " AND archival_tag.subcategory=\"$this->subcategory\" 
                 ORDER BY archival_tag.rank_now ASC 
                 LIMIT 1 OFFSET $threshold"
            )
        ) {
            return false;
        }
        if ($result->fetch()) {
            //TODO compare log10s, then decimal
            return true;
        }
        //not enough on the list to begin with, so it fits
        return true;
    }
}
