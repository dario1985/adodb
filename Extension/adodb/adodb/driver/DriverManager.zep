/*
 * Copyright 2014 (c) Dario Mancuso
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace ADOdb\Driver;

class DriverManager
{
    public static function create(<\ADOdb\DataSource> dso) -> <\ADOdb\Driver>
    {
        switch (dso->getType()) {
            // All mysql* to PDO
            case "mysqli":
            case "mysqlt":
                $dso->setType("mysql");
            case "mysql":
            case "sqlite":
            case "sqlite2":
            case "pdo":
                return new PDO\Driver(dso);
        }
        throw new \Exception("No valid Driver found for this source");
    }
}