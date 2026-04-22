import json
from fpdf import FPDF

class PDF(FPDF):
    def header(self):
        self.set_font('helvetica', 'B', 16)
        self.cell(0, 10, 'SonarCloud Static Analysis Report', align='C')
        self.ln(10)
        self.set_font('helvetica', 'I', 10)
        self.cell(0, 10, 'Elmenus Management System - Phase 1', align='C')
        self.ln(15)

def generate_report():
    try:
        with open('my_issues.json', 'r') as file:
            data = json.load(file)
    except FileNotFoundError:
        print("Error: my_issues.json not found. Run the curl command first.")
        print("curl -u 6ffccf5176f47d66e243063b34d92d681c11df80: \"https://sonarcloud.io/api/issues/search?componentKeys=anas4208-workspace_anas4208-workspace&ps=100\" > my_issues.json")
        return

    issues = data.get('issues', [])

    pdf = PDF()
    pdf.add_page()

    if not issues:
        pdf.set_font('helvetica', '', 12)
        pdf.cell(0, 10, "No issues found or JSON is empty.", ln=True)
    else:
        # Add summary
        pdf.set_font('helvetica', 'B', 12)
        pdf.cell(0, 10, f"Total Issues Found: {len(issues)}", ln=True)
        pdf.ln(5)
        
        for i, issue in enumerate(issues, 1):
            severity = issue.get('severity', 'INFO')
            component = issue.get('component', 'Unknown file').split(':')[-1]
            line = issue.get('textRange', {}).get('startLine', issue.get('line', 'N/A'))
            message = issue.get('message', 'No description')
            issue_type = issue.get('type', 'Unknown')
            
            # Color coding based on severity
            if severity == 'CRITICAL':
                pdf.set_text_color(255, 0, 0)
            elif severity == 'MAJOR':
                pdf.set_text_color(255, 165, 0)
            elif severity == 'MINOR':
                pdf.set_text_color(0, 128, 0)
            else:
                pdf.set_text_color(0, 0, 0)
            
            pdf.set_font('helvetica', 'B', 11)
            pdf.cell(0, 8, f"{i}. [{severity}] {issue_type}: {component} (Line {line})", ln=True)
            
            pdf.set_text_color(0, 0, 0)
            pdf.set_font('helvetica', '', 10)
            pdf.multi_cell(0, 6, f"   {message}")
            pdf.ln(3)

    pdf.output('SonarCloud_Issues_Report.pdf')
    print(f"✅ Generated SonarCloud_Issues_Report.pdf with {len(issues)} issues.")

if __name__ == "__main__":
    generate_report()
