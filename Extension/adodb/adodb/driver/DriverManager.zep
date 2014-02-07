namespace ADOdb\Driver;

class DriverManager
{
    public static function create(var dso)
    {
        switch (dso->getType()) {
            // All mysql* to PDO
            case "mysqli":
            case "mysqlt":
                $dso->setType("mysql");
            case "mysql":
            case "pdo":
                return new PDO\Driver(dso);
        }
        throw new \Exception("No valid Driver found for this source");
    }
}