<?php
   $conn=mysqli_connect("localhost", "root", "", "iot");
   if(!$conn){ 
      echo("not ok");
   }
   $count = "SELECT COUNT(*) as c FROM irrigation";
   $res_count=mysqli_query($conn,$count);
   $row_count = mysqli_fetch_array($res_count);
   $offsetValue = (($row_count['c'] - 10) > 0) ? ($row_count['c'] - 10) : 0;
   $sql ="SELECT * FROM irrigation LIMIT 10 OFFSET $offsetValue";
   $ret=mysqli_query($conn,$sql);
   $response = array();
   $moisture = array();
   $humidity = array();
   $temperature = array();
   if(!$ret){
   while($row = mysqli_fetch_array($ret)) {
      $moist_value = array();
      $humid_value = array();
      $temp_value = array();
      array_push($moist_value, $row["time"]);
      array_push($moist_value, $row["moisture"]);
      array_push($humid_value, $row["time"]);
      array_push($humid_value, $row["humidity"]);
      array_push($temp_value, $row["time"]);
      array_push($temp_value, $row["temperature"]);
      array_push($moisture, $moist_value);
      array_push($humidity, $humid_value);
      array_push($temperature, $temp_value);
   }
   // echo "<script>console.log('$response');</script>";
   array_push($response, $moisture);
   array_push($response, $humidity);
   array_push($response, $temperature);
   echo json_encode($response);
}
?>
