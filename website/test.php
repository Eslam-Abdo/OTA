
<?php

  if( $_POST['burn'] == 'no_file')
  {

  }
  else if ( $_POST['burn'] == 'ok')
  { 
      /* Open the file */
      $myfile = fopen("lengthPtr.txt","w");
      fwrite($myfile,'0');
      /* Close the file */
      fclose($myfile);
      $_POST['burn'] = 'done';
      header ("Location: StartBurn.html");
      //echo "start";
  }

  $files = glob('uploads/*'); // get all file names

  if (is_file($files[0]))
  {
      $path = $files[0];
      $mydata = file($path); //read file in array
      $length = count($mydata);

      if ( isset( $_GET['config'] ) )
      {
        /* Open the file */
        $myfile = fopen("lengthPtr.txt","r");
        $ptr =  fgets($myfile);
        fclose($myfile);


        if (( $_GET['config'] == 'ok') && ($ptr < $length))
        {
            echo $mydata[$ptr];
            $ptr++ ;
            $myfile = fopen("lengthPtr.txt","w");
            fwrite($myfile,$ptr);
            fclose($myfile);
            //header ("Location: test.php?config=none");
        }
        elseif ( $_GET['config'] == 'none')
        {
            //echo ($ptr-1);
            echo $mydata[$ptr-1];

        }
        elseif (($ptr == $length) || ($_GET['config'] == 'doneBurn'))
        {
            echo "DONE UPLOAD ";
            /* Open the file */
            $myfile = fopen("lengthPtr.txt","w");
            fwrite($myfile,'-1');
            /* Close the file */
            fclose($myfile);

            if(is_file($files[0])) 
            {
              unlink($files[0]); // delete file
            }
	    header ("Location: Finish.html");
        }
	elseif ( $_GET['config'] == 'allfile')
	{
		foreach($mydata as $line)
		{
			echo $line ."%";
		}
	}

	elseif ( $_GET['config'] == 'filelength')
	{
		echo $length ;
	}

      }
  }
  else
  {
      /* No files Found */
      if ( isset( $_GET['config'] ) )
      {
          if ($_GET['config'] == 'ok')
          {
              echo "NO FILE FOUND "."%";
          }
          elseif ( $_GET['config'] == 'none')
          {
              echo "NO FILE FOUND "."%";
          }
      }

  }


?>