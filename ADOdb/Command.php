<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

abstract class Command
{
    protected $connection;

    /**
     * Run the command using connection
     *
     * @return mixed | null
     */
    final public function execute(Connection $connection)
    {
        $this->connection = $connection;
        if ($rs = $this->doQuery()) {
            return $this->processResults($rs);
        }
    }

    /**
     * doQuery
     *
     * @return RecordSet | null
     */
    abstract protected function doQuery();

    /**
     * processResults: Postprocess the results in some way
     */
    abstract protected function processResults();
}
