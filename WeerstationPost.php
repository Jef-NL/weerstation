<?php 
// 1. database credentials
$host = "databases.aii.avans.nl";
$db_name = "hjbaars_db2";
$username = "hjbaars";
$password = "Ab12345";
$api_key_value = "tPmAT5Ab3j7F9";
 
$api_key= $temp = $humid = "";

if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
    if($api_key == $api_key_value) {
        $temp = test_input($_POST["temp"]);
        $humid = test_input($_POST["humid"]);
		$pressure = test_input($_POST["pressure"]);
		$lux = test_input($_POST["lux"]);
		$date = test_input($_POST["date"]);
        
        // Create connection
        $conn = new mysqli($host, $username, $password, $db_name);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
        $sql = "INSERT INTO weerstation (temp, humid, pressure, lightlux, TIME)
        VALUES ('" . $temp . "', '" . $humid . "', '" . $pressure . "', '" . $lux. "', date_sub( Now(), INTERVAL ('". $date."') MINUTE))";
        
        if ($conn->query($sql) === TRUE) {
            echo "New record created successfully";
        } 
        else {
            echo "Error: " . $sql . "<br>" . $conn->error;
        }
    
        $conn->close();
    }
    else {
        echo "Wrong API Key provided.";
    }

}
else {
    echo "No data posted with HTTP POST.";
}

function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
?>