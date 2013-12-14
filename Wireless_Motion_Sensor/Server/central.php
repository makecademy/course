<?php
	
	// Load XML file
	$central = simplexml_load_file('central.xml');
	echo "<div class='device_title'>Home</div>";
	
  // Echo XML file, parse devices
	foreach($central->children() as $child) {
		  
      echo "<div class='device'>";
  		echo $child->getName()." ";
  		
  		// Parse attributes of devices
  		foreach($child->children() as $subchild) {

  			if ($subchild->getName() == "Type"){
  				$type = $subchild;
  			}

  			if ($subchild->getName() == "Value"){

  				if ($type == "motion"){
  					if($subchild == "Off") {
  						echo "<div class='off'></div>";
  					}

  					if($subchild == "On") {
  						echo "<div class='on'></div>";
  					}
  				}
  				
  			}

  			// If a device is not registered, propose to register
    		if ($subchild->getName() == "Registered" && $subchild == "False"){
    			echo "<input id='register' value='Register device' type='submit'>
    			<script src='jquery-2.0.3.min.js'></script>
					<script type='text/javascript'>
           				$('#register').click(function(){
                 			$.get('interface.php',{device:'".$child->getName()."',phase:'operation'});
            			});
    				</script>";
    		}
  		}
  		echo "</div>";
	}

?>