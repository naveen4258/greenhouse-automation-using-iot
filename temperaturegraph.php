<?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "iot";
// Create connection
$conn = mysqli_connect($servername, $username, $password, $dbname);
// Check connection
if (!$conn) {
    die("Connection failed: " . mysqli_connect_error());
}
$sql = "select sno,temperature,times1 from irrigation ORDER BY sno ASC";
$result = mysqli_query($conn, $sql);
if (mysqli_num_rows($result) > 0) {
    // output data of each row
    $dataPoints = array();
    while($row = mysqli_fetch_assoc($result)) {
    	$value=$row['temperature'];
    	$timer=$row['times1'];
    	array_push($dataPoints,array("y"=>$value,"label"=>$timer));
}
}
$page = $_SERVER['PHP_SELF'];
$sec = "10";
mysqli_close($conn); 
?>
<!DOCTYPE HTML>
<html>
<head>
	 <meta http-equiv="refresh" content="<?php echo $sec?>;URL='<?php echo $page?>'">
<script>
window.onload = function () {
 
var chart = new CanvasJS.Chart("chartContainer", {
	title: {
		text: "Temperature Sensor Readings"
	},
	axisY: {
		title: "values"
	},
	data: [{
		type: "line",
		dataPoints: <?php echo json_encode($dataPoints, JSON_NUMERIC_CHECK); ?>
	}]
});
chart.render();
 
}
</script>
</head>
<body>
<div id="chartContainer" style="height: 370px; width: 100%;"></div>
<script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>
</body>
</html>