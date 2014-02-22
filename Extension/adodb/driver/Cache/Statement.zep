/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\Cache;

use ADOdb\FieldObject as ADODB_FieldObject;

class Statement implements \ADOdb\Statement
{
    const FETCH_NUM = 1;
    const FETCH_ASSOC = 2;
    const FETCH_BOTH = 3;
    const FETCH_NORMAL = self::FETCH_ASSOC;

    protected resultsetData;
    protected rowCount;
    protected columnMeta;
    protected columnMap;

    protected lastErrorCode;
    protected lastErrorInfo;
    protected currentRow;
    protected timeCreated;
    protected fetchMode = self::FETCH_ASSOC;
    protected data;

    // public function __construct(array data = null) don't work
    public function __construct(data = null)
    {
        if (isset(data["COLUMN_META"]) && isset(data["RESULTSET"])) {
            let this->columnMeta = data["COLUMN_META"];
            this->initResultsetData(data["RESULTSET"]);
            if (isset(data["CREATED"])) {
                let this->timeCreated = (int) data["CREATED"];
            }
            let this->rowCount = count(this->resultsetData);
            let this->currentRow = 0;
        } else {
            throw new \InvalidArgumentException("Invalid data");
        }
    }

    protected function initResultsetData(array resultsetRawData)
    {
        let this->columnMap = [];
        let this->resultsetData = resultsetRawData;
        var c;
        for c in this->columnMeta {
            let this->columnMap[] = c["name"];
        }
    }

    public function __destruct()
    {
        let this->data = null;
        let this->columnMap = null;
        let this->columnMeta = null;
    }

    public function timeCreated()
    {
        return this->timeCreated;
    }

    public function canSeek()
    {
        return true;
    }

    public function close()
    {
        return true;
    }

    public function errorCode()
    {
        return this->lastErrorCode;
    }

    public function errorInfo()
    {
        return this->lastErrorInfo;
    }

    public function execute(parameters)
    {
        return true;
    }

    public function columnCount()
    {
        return count(this->columnMeta);
    }

    public function rowCount()
    {
        return this->rowCount;
    }

    public function $fetch(offset = null)
    {
        if (offset === null) {
            let this->currentRow++;
            let offset = this->currentRow;
        }

        if (offset < this->rowCount) {
            var row; let row = this->resultsetData[offset];
            if (this->fetchMode & self::FETCH_ASSOC) {
                if (this->fetchMode & self::FETCH_NUM) {
                    return array_merge(
                        row, array_combine(this->columnMap, row)
                    );
                } else {
                    return array_combine(this->columnMap, row);
                }
            } else {
                return row;
            }
        } else {
            return false;
        }
    }

    public function fetchAll(fetch_style = null)
    {
        let fetch_style = fetch_style !== null ? fetch_style : this->fetchMode;

        if (fetch_style & self::FETCH_ASSOC) {
            var data, row; let data = [];
            if (fetch_style & self::FETCH_NUM) {
                for row in this->resultsetData {
                    let data[] = array_merge(
                        row,
                        array_combine(this->columnMap, row)
                    );
                }
            } else {
                for row in this->resultsetData {
                    let data[] = array_combine(this->columnMap, row);
                }
            }
            return data;
        } else {
            return this->resultsetData;
        }
    }

    public function fetchColumn(column_number = 0)
    {
        if (this->currentRow < this->rowCount) {
            let this->currentRow++;
            return this->resultsetData[this->currentRow - 1][column_number];
        } else {
            return false;
        }
    }

    public function getColumnMeta(column_number = 0)
    {
        return new ADODB_FieldObject(this->columnMeta[column_number]);
    }

    public function setFetchMode(mode)
    {
        let this->fetchMode = mode;
    }

    public function dump()
    {
        return [
            "RESULTSET" : this->fetchAll(self::FETCH_NUM),
            "COLUMN_META" : this->columnMeta,
            "CREATED" : this->timeCreated
        ];
    }
}