import xml.etree.ElementTree as ET
import subprocess
import os

# Run gcovr and capture output
result = subprocess.run(['gcovr', '--root', '.', '--xml'], 
                       capture_output=True, text=True)

if result.returncode == 0:
    # Parse the gcovr output
    try:
        root = ET.fromstring(result.stdout)
        
        # Create SonarQube format
        sonar_root = ET.Element('coverage')
        sonar_root.set('version', '1')
        
        for file_elem in root.findall('.//file'):
            filename = file_elem.get('name')
            sonar_file = ET.SubElement(sonar_root, 'file')
            sonar_file.set('path', filename)
            
            for line_elem in file_elem.findall('.//line'):
                line_num = line_elem.get('number')
                hits = line_elem.get('hits')
                if hits and int(hits) > 0:
                    line_cover = ET.SubElement(sonar_file, 'lineToCover')
                    line_cover.set('lineNumber', line_num)
                    line_cover.set('covered', 'true')
                elif hits and int(hits) == 0:
                    line_cover = ET.SubElement(sonar_file, 'lineToCover')
                    line_cover.set('lineNumber', line_num)
                    line_cover.set('covered', 'false')
        
        # Write the new file
        tree = ET.ElementTree(sonar_root)
        tree.write('coverage.xml', encoding='UTF-8', xml_declaration=True)
        print("✓ Fixed coverage.xml generated successfully!")
        
    except ET.ParseError as e:
        print(f"Error parsing XML: {e}")
else:
    print("Error running gcovr")
    print(result.stderr)
