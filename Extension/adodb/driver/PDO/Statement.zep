/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\PDO;

class Statement implements \ADOdb\Statement
{
    const FETCH_NUM = 3; // Driver::FETCH_NUM;
    const FETCH_ASSOC = 2; // Driver::FETCH_ASSOC;
    const FETCH_BOTH = 4; // Driver::FETCH_BOTH;
    
    protected timeCreated;
    protected st;

    protected function __construct(<\PDOStatement> statement)
    {
        let this->st = statement;
        let this->timeCreated = time();
    }
    
    public function timeCreated()
    {
        return this->timeCreated;
    }
    
    public function canSeek()
    {
        return false;
    }
    
    public function close()
    {
        return this->st->closeCursor();
    }
    
    public function getColumnMeta(column_number = 0)
    {
        var pdo_metas; let pdo_metas = this->st->getColumnMeta(column_number);
        return new \ADOdb\FieldObject(
                [
                    "name" : pdo_metas["name"],
                    "max_length" : pdo_metas["len"],
                    "type" : pdo_metas["native_type"]
                ]);
    }

    public function columnCount() -> int
    {
        return this->st->columnCount();
    }

    public function dump()
    {
        var metas; let metas = [];
        int col = 0;
        var nCols; let nCols = this->columnCount();
        while (col < nCols) {
            var pdo_metas; let pdo_metas = this->st->getColumnMeta(col);
            let metas[] = [
                "name" : pdo_metas["name"],
                "max_length" : pdo_metas["len"],
                "type" : pdo_metas["native_type"]
            ];
            let col++;
        }
        return [
            "RESULTSET" : this->fetchAll(self::FETCH_NUM), 
            "COLUMN_META" : metas, 
            "CREATED" : this->timeCreated
        ];
    }

    public function errorCode()
    {
        return this->st->errorCode();
    }

    public function errorInfo()
    {
        return this->st->errorInfo();
    }

    public function rowCount() -> int
    {
        return this->st->rowCount();
    }

    public function execute(parameters)
    {
        return this->st->execute(parameters);
    }

    public function $fetch(int offset = null)
    {
        return this->st->$fetch(offset);
    }

    public function fetchAll(fetch_style = null)
    {
        return this->st->fetchAll(fetch_style);
    }

    public function fetchColumn(int column_number = 0)
    {
        return this->st->fetchColumn(column_number);
    }

    public function setFetchMode(mode)
    {
        return this->st->setFetchMode(mode);
    }
}