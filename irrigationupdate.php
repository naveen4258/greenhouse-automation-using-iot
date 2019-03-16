
<?php
	
	$conn=mysqli_connect("localhost", "root", "", "iot");
	$moisture=0;
	$humidity=0;
	$temperature=0;
	$moisture = $_POST[ 'moisture' ];
	
	$humidity = $_POST[ 'humidity' ];
	
	$temperature = $_POST['temperature'];
	
	$sql = "insert into irrigation(moisture,humidity,temperature) values('$moisture','$humidity','$temperature');";

	// error_log($sql);

	$res=mysqli_query($conn,$sql);
	if($res)
	
		echo "success";
	
	
	// echo "Shanavaz";
?>