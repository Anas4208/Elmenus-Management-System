import json
from fpdf import FPDF

class PDF(FPDF):
    def header(self):
        self.set_font('helvetica', 'B', 16)
        self.cell(0, 10, 'Phase 1: SonarCloud Static Analysis Report', align='C', ln=True)
        self.ln(10)

def generate_report():
    # Load the JSON data
    try:
        with open('my_issues.json', 'r') as file:
            data = json.load(file)
    except FileNotFoundError:
        print("Error: my_issues.json not found. Run the curl command first.")
        return

    issues = data.get('issues', [])
    
    pdf = PDF()
    pdf.add_page()

    if not issues:
        pdf.set_font('helvetica', '', 12)
        pdf.cell(0, 10, "No issues found or JSON is empty.", ln=True)
    else:
        for i, issue in enumerate(issues, 1):
            severity = issue.get('severity', 'INFO')
            # Clean up the file path to just show the filename
            component = issue.get('component', 'Unknown file').split(':')[-1]
            line = issue.get('textRange', {}).get('startLine', issue.get('line', 'N/A'))
            message = issue.get('message', 'No description')

            # Issue Header
            pdf.set_font('helvetica', 'B', 11)
            pdf.cell(0, 8, f"{i}. [{severity}] File: {component} (Line {line})", ln=True)
            
            # Issue Description
            pdf.set_font('helvetica', '', 10)
            pdf.multi_cell(0, 6, txt=message)
            pdf.ln(5)

    pdf.output('SonarCloud_Official_Report.pdf')
    print(f"SUCCESS: Generated SonarCloud_Official_Report.pdf with {len(issues)} issues.")

if __name__ == "__main__":
    generate_report()
