<?php

  // Respond to GET requests
  if ($_GET) {

    // Initialization phases
    if ($_GET["device"] && $_GET["phase"]) {

      // Normal operation phase
      if ($_GET["phase"] == "operation") {

        $central = simplexml_load_file('central.xml');

        $central->$_GET["device"]->Registered = "True";
        $central->$_GET["device"]->addChild("Value", "Off"); 

        $central->asXML('central.xml');

      }

    }

  }

?>