var app = angular.module('myApp', ['ngRoute']);
app.config(['$routeProvider',
function($routeProvider) {
     $routeProvider.
         when('/', {
             templateUrl: 'chart.html',
         }).
         when('/irrigation', {
             templateUrl: 'irrigation.html',
         }).
         otherwise({
             redirectTo: '/'
         });
}]);
app.controller('irrigationCtrl', function($scope, $http) {
    var irrigationchart = Highcharts.chart('irrigation', {
	    chart: {
	        type: 'spline'
	    },
	    title: {
	        text: 'Time Series Visualization'
	    },
	    xAxis: {
	        type: 'category',
	        title: {
	            text: 'Date Time'
	        }
	    },
	    yAxis: {
	        title: {
	            text: 'Sensor Values'
	        },
	        min: 0
	    },
	    tooltip: {
	        headerFormat: '<b>{series.name}</b><br>',
	        pointFormat: '{point.y:.2f}',
	        style: {
 				color: 'blue',
    			fontWeight: 'bold'
			}
	    },

	    plotOptions: {
	        spline: {
	            marker: {
	                enabled: true
	            }
	        },
	        series: {
 			   pointStart: Date.UTC(2010, 0, 1),
			   pointInterval: 5 * 60 * 1000 // one day
			}
	    },

	    colors: ['#6CF', '#39F', '#06C', '#036', '#000'],

	    series: [
	    	{
		        name: "Moisture",
		        data: [
		        ]
	    	},
	    	{
		        name: "Humidity",
		        data: [
		        ]
		    },
		    {
		        name: "Temperature",
		        data: [
	     	   ]
	     	}
	    ]	
	});
	$scope.getData = function(){
	    $http({
    		method : "POST",
    		url : "irrigation.php"
		}).then(function(response) {
	        $scope.data = response.data;
	        console.log(response.data);
	        console.log($scope.data[0]);
	        console.log($scope.data[1]);
	        console.log($scope.data[2]);
	        irrigationchart.update({
	        	series: [
	        	{
		        	name: "Moisture",
		        	data: $scope.data[0]
	        	},
	        	{
		        	name: "Humidity",
		        	data: $scope.data[1]
	        	},
	        	{
		        	name: "Temperature",
		        	data: $scope.data[2]
	        	}
	        	]
	        });
	    });
	}
	$scope.getData();
	setInterval(function() { 
		$scope.getData();
	}, 1000);
});