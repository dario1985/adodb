/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb;

abstract class Command
{
    protected connection;

    /**
     * Run the command using connection
     *
     * @return mixed | null
     */
    final public function execute(<Connection> connection)
    {
        let this->connection = connection;
        var rs; let rs = this->doQuery();
        if (rs) {
            return this->processResults(rs);
        }
    }

    /**
     * doQuery
     *
     * @return ResultSet | null
     */
    protected function doQuery() -> <ResultSet>
    {
        throw new \BadMethodCallException("Abstract method not implemented");
    }

    /**
     * processResults: Postprocess the results in some way
     */
    protected function processResults(<ResultSet> rs)
    {
        throw new \BadMethodCallException("Abstract method not implemented");
    }
}