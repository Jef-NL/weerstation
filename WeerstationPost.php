<?php 
// 1. database credentials
$host = "databases.aii.avans.nl";
$db_name = "hjbaars_db2";
$username = "hjbaars";
$password = "Ab12345";
$api_key_value = "tPmAT5Ab3j7F9";

// 2. Init variables 
$api_key = $temp = $humid = $pressure = $lux = $date ="";

// 3. Check for Post request
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $api_key = test_input($_POST["api_key"]);
	
	// 4. Store post variables in to local variables
    if($api_key == $api_key_value) {
        $temp = test_input($_POST["temp"]);
        $humid = test_input($_POST["humid"]);
		$pressure = test_input($_POST["pressure"]);
		$lux = test_input($_POST["lux"]);
		$date = test_input($_POST["date"]);
        
        // 5. Create connection
        $conn = new mysqli($host, $username, $password, $db_name);
        // Check connection
        if ($conn->connect_error) {
            die("Connection failed: " . $conn->connect_error);
        } 
        
		// 6. Build Query
        $sql = "INSERT INTO tblweatherstation (floTemp, floHumid, floPressure, floLightlux, TIME)
        VALUES ('" . $temp . "', '" . $humid . "', '" . $pressure . "', '" . $lux. "', date_sub( Now(), INTERVAL ('". $date."') MINUTE))";
        
		// 7. Send Query
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

// Split data
function test_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}
?>