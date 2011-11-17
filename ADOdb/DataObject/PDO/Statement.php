<?php
/*
 * Copyright 2011 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\DataObject\PDO;

class Statement extends \PDOStatement
                implements \ADOdb\Statement
{

    public function canSeek()
    {
        return false;
    }
}
