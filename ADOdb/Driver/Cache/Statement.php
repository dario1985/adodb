<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver\Cache;

use ADOdb\FieldObject as ADODB_FieldObject;

class Statement implements \ADOdb\Statement
{
    const FETCH_NORMAL = self::FETCH_ASSOC;
    const FETCH_NUM = 1;
    const FETCH_ASSOC = 2;
    const FETCH_BOTH = 3;
    
    protected $resultsetData;
    protected $rowCount;
    protected $columnMeta;
    protected $columnMap;

    protected $lastErrorCode;
    protected $lastErrorInfo;
    protected $currentRow;
    protected $timeCreated;
    protected $fetchMode = self::FETCH_ASSOC;

    public function __construct(array $data = null)
    {
        if (isset($data['COLUMN_META']) && isset($data['RESULTSET'])) {
            $this->columnMeta = $data['COLUMN_META'];
            $this->initResultsetData($data['RESULTSET']);
            if (isset($data['CREATED'])) {
                $this->timeCreated = (int) $data['CREATED'];
            }
            $this->rowCount = count($this->resultsetData);
            $this->currentRow = 0;
        } else {
            throw new \InvalidArgumentException('Invalid data');
        }
    }

    protected function initResultsetData(array $resultsetRawData)
    {
        $this->columnMap = array();
        $this->resultsetData = $resultsetRawData;
        foreach ($this->columnMeta as $c) {
            $this->columnMap[] = $c['name'];
        }
    }
    
    public function __destruct()
    {
        $this->data = $this->columnMap = $this->columnMeta = null;
    }

    public function timeCreated()
    {
        return $this->timeCreated;
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
        return $this->rowCount;
    }

    public function fetch($offset = null)
    {
        if ($offset === null) {
            $offset = $this->currentRow++;
        }
        
        if ($offset < $this->rowCount) {
            $row = $this->resultsetData[$offset];
            if ($this->fetchMode & self::FETCH_ASSOC) {
                if ($this->fetchMode & self::FETCH_NUM) {
                    return array_merge(
                        $row, array_combine($this->columnMap, $row)
                    );
                } else {
                    return array_combine($this->columnMap, $row);
                }
            } else {
                return $row;
            }
        } else return false;
    }

    public function fetchAll($fetch_style = null)
    {
        $fetch_style = $fetch_style !== null ? $fetch_style : $this->fetchMode;
        
        if ($this->fetchMode & self::FETCH_ASSOC) {
            $data = array();
            if ($this->fetchMode & self::FETCH_NUM) {
                foreach ($this->resultsetData as $row)
                    $data[] = array_merge(
                        $row, 
                        array_combine($this->columnMap, $row)
                    );
            } else {
                foreach ($this->resultsetData as $row)
                    $data[] = array_combine($this->columnMap, $row);
            }
            return $data;
        } else {
            return $this->resultsetData;
        }
    }

    public function fetchColumn($column_number = 0)
    {
        if ($this->currentRow < $this->rowCount) {
            return $this->resultsetData[$this->currentRow++][$column_number];
        } else return false;
    }

    public function getColumnMeta($column_number = 0)
    {
        return new ADODB_FieldObject($this->columnMeta[$column_number]);
    }
    
    public function setFetchMode($mode)
    {
        $this->fetchMode = $mode;
    }
    
    public function dump()
    {
        throw new \RuntimeException('Cannot dump a cached statement');
    }
}
