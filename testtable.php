<!DOCTYPE html>
<html>
<script>
	function showValues(){
		var value=[10,20,30,40,50];
		var n=value.length;
		var canvas = document.getElementById("myCanvas");
			var ctx = canvas.getContext("2d");
			ctx.moveTo(0,0);
		for(i=0;i<n;i++){
			ctx.lineTo(i*10,value[i]);
			}
			ctx.stroke();
	}
</script>
<body>
	<canvas id="myCanvas" width="1200" height="700"
style="border:1px solid #d3d3d3;">
Your browser does not support the canvas element.
</canvas>
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
$sql = "SELECT moisture FROM irrigation";
$result = mysqli_query($conn, $sql);
if (mysqli_num_rows($result) > 0) {
    // output data of each row
    $i=0;
    $deta=array();
    while($row = mysqli_fetch_assoc($result)) {
        $deta[$i]=$row['moisture'];
        $i++;
    }?>
    <button onclick="showValues()">moisture</button>
<?php
} 
mysqli_close($conn);
?>
</body>
</html>