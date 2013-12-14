<?php

	// Normal operation
	if ($_GET['device'] && $_GET['phase']) {

		$device = $_GET['device'];
		$phase = $_GET['phase'];
    	
		// Detection phase
		if ($phase == "detection") {

			$central = simplexml_load_file('central.xml');

			if (isset($central->$device->Registered)) {
				$answer = "Device detected";
			}

			else {

				$module = $central->addchild($device);
				$module->addChild("Registered", "False");
				$module->addChild("Type", preg_replace("/[^a-zA-Z]+/", "", $device));
				$central->asXML('central.xml');
				$answer = "Device detected";

			}

		}

		// Registration phase
		if ($phase == "registration") {

			$central = simplexml_load_file('central.xml');

			if ($central->$device->Registered == "True") {
				$answer = "Device registered";
			}
			else {
				$answer = "Not yet registered";
			}

		}

		if ($phase == "receive") {

				$central = simplexml_load_file('central.xml');
			    $central->$device->Value = $_GET['data'];
			    $central->asXML('central.xml');
			    $answer = "Data received";
		}

		// Answer
		echo $answer;

	}

?>