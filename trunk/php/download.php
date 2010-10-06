<?php                        
    $wheatFile=file("wheat/DownloadLocation.txt");     
    $pwaolFile="pwaol/Play%20Worms%20Armageddon%20on%20linux.7z"; 
    $fxFile="ProSnooperFx/ProSnooperFx.rar"; 
    if(isset($_POST['downloadWheat']))    {        
        header('Content-disposition: attachment; filename=TheWheatSnooperwin32.exe'); 
        header("Content-Transfer-Encoding: binary"); 
        header('Content-type: application/exe'); 
        $s='wheat/'.trim($wheatFile[0]);
        header("Content-Length: ".filesize($s)); 
        readfile($s);    
    } 
    if(isset($_POST['downloadPwaol']))    { 
        header('Content-disposition: attachment; filename='.$pwaolFile); 
        header("Content-Transfer-Encoding: binary"); 
        header('Content-type: application/exe'); 
        header("Content-Length: ".filesize($pwaolFile)); 
        readfile($pwaolFile);    
    } 
    if(isset($_POST['downloadFx']))    { 
        header('Content-disposition: attachment; filename='.$fxFile); 
        header("Content-Transfer-Encoding: binary"); 
        header('Content-type: application/exe'); 
        header("Content-Length: ".filesize($fxFile)); 
        readfile($fxFile);    
    } 
    $counter=file("downloadCounter.txt"); 
    for($i=0;$i<=2;$i++){ 
        $counter[$i]=trim($counter[$i]);        
    }        
    $save=false; 
    if(isset($_POST['downloadWheat']))    {        
        $counter[0]++;        
        $save=true;        
    } 
    if(isset($_POST['downloadPwaol']))    {        
        $counter[1]++; 
        $save=true;        
    }          
    if(isset($_POST['downloadFx']))    {        
        $counter[2]++; 
        $save=true;        
    }            
    if($save){ 
        $file=fopen("downloadCounter.txt","w+"); 
        fputs($file,($counter[0]."\n".$counter[1]."\n".$counter[2])); 
        fclose($file);        
    } 
?>        
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 3.2//EN"> 
<html> 
    <head> 
        <meta name="generator" content="HTML Tidy for Windows (vers 14 February 2006), see www.w3.org"> 
 
        <title>Download</title>  
 
        <link rel="shortcut icon" href="icon/pwaolIcon.png"/> 
        <style type="text/css"> 
        table{ 
            width:400px; 
        } 
            table td { 
                border:2px; 
                border-style: ridge; 
                border-width: 3px; 
                border-style: outset; 
                border-color: black; 
                text-align: center; 
                padding: 5px; 
                background-color: silver;  
            } 
            body{                
                text-align:center; 
                width:400px; 
                margin:0px auto;                
                margin-top :50px; 
                padding:15px; 
                border:1px dashed #333; 
                background-color:#eee; 
            }                    
            .footNode{
                font-size: 11;
            }
        </style> 
    </head> 
 
    <body>            
        <form action="download.php" method="post" name="downloadForm">     
            <table class="downloadTable"> 
                <tr>                  
                    <td><img src="icon/wheatIcon.png" alt="Icon"></td> 
                    <td> 
                        The Wheat Snooper <br/>Version <?php echo $wheatFile[1]?><br/> 
                        <input value="Download" type="submit" name="downloadWheat"> </td> 
                    <td> 
                        <label >Downloads:</label> 
                        <label><?php echo $counter[0]?></label> 
                    </td>  
                </tr> 
                <tr>                
                    <td> <img src="icon/pwaolIcon.png" alt="Icon">  </td> 
                    <td> 
                        Play Worms Armageddon on Linux <br/> 
                        <input value="Download" type="submit" name="downloadPwaol"></td> 
                    <td> 
                        <label >Downloads:</label> 
                        <label><?php echo $counter[1]?></label> 
                    </td>          
                </tr> 
                <tr>                    
                    <td><img src="icon/fxIcon.png" alt="Icon"> </td> 
                    <td> 
                        ProSnooperFx<br/> 
                        <input value="Download" type="submit" name="downloadFx"></td> 
                    <td> 
                        <label >Downloads:</label> 
                        <label><?php echo $counter[2]?></label> 
                    </td>          
                </tr> 
            </table> 
            <div class="footNode">
            The programs are written by Lookias. 
            All programs here, but ProSnooperFx, are licensed with the <a href="http://en.wikipedia.org/wiki/GNU_General_Public_License">GPL</a> version 2. 
            There is also a <a href="http://lookias.worms2d.info/forum/">forum</a> dedicated to these programs, 
            you can get a support there and post your own wishes and ideas.</div>
        </form>    
    </body>      
</html> 