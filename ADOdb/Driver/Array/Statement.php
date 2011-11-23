<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\Array;

use ADOdb\FieldObject as ADODB_FieldObject;

class Statement implements \ADOdb\Statement
{
    protected $resultsetData;
    protected $columnMeta;

    protected $lastErrorCode;
    protected $lastErrorInfo;
    protected $currentRow;

    protected $createdTime;

    protected function __construct(array $data = null)
    {
        $this->createdTime = time();
        if (isset($data['COLUMN_META']) && isset($data['RESULTSET'])) {
            $this->columnMeta = $data['COLUMN_META'];
            $this->buildResultsetData($data['RESULTSET']);
            if (isset($data['CREATED'])) {
                $this->createdTime = (int) $data['CREATED'];
            }
        } else {
            throw new InvalidArgumentException('Invalid data');
        }
    }

    protected function buildResultsetData(array $resultsetRawData)
    {
        $this->resultsetData = $colNames = array();
        foreach ($this->columnMeta as $c) {
            $colNames[] = $c['name'];
        }
        foreach ($resultsetRawData as $record) {
            $this->resultsetData[] = array_combine($colNames, $record);
        }
    }

    protected function __destruct()
    {
        $this->data = null;
    }

    public function createdTime()
    {
        return $this->createdTime();
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
        return $this->lastErrorCode;
    }

    public function errorInfo()
    {
        return $this->lastErrorInfo;
    }

    public function execute($parameters)
    {
        return true;
    }

    public function columnCount()
    {
        return count($this->columnMeta);
    }

    public function rowCount()
    {
        return count($this->resultsetData);
    }

    public function fetch($offset = null)
    {
        if ($offset === null) {
            $offset = $this->currentRow++;
        }
        return $this->resultsetData[$offset];
    }

    public function fetchAll()
    {
        return $this->resultsetData;
    }

    public function fetchColumn($column_number = 0)
    {
        return $this->resultsetData[$this->currentRow++][$column_number];
    }

    public function getColumnMeta($column_number = 0)
    {
        $field = new ADODB_FieldObject();
        $field->_setDataInfo($this->columnMeta[$column_number]);
        return $field;
    }
}
