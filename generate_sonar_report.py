from fpdf import FPDF
import json
from datetime import datetime

# Load real data
with open('metrics.json', 'r') as f:
    metrics_data = json.load(f)

with open('issues.json', 'r') as f:
    issues_data = json.load(f)

# Extract metrics
metrics = {}
for m in metrics_data.get('component', {}).get('measures', []):
    metrics[m['metric']] = m['value']

# Extract issues
issues = issues_data.get('issues', [])

class PDF(FPDF):
    def header(self):
        self.set_font('helvetica', 'B', 16)
        self.cell(0, 10, 'Elmenus Management System', ln=True, align='C')
        self.set_font('helvetica', 'I', 10)
        self.cell(0, 5, 'SonarCloud Quality Report', ln=True, align='C')
        self.ln(10)
        self.line(10, 30, 200, 30)
        self.ln(10)
    
    def footer(self):
        self.set_y(-15)
        self.set_font('helvetica', 'I', 8)
        self.cell(0, 10, f'Generated: {datetime.now().strftime("%Y-%m-%d %H:%M:%S")}', ln=True, align='C')

# Create PDF
pdf = PDF()
pdf.add_page()

# Project Info
pdf.set_font('helvetica', 'B', 12)
pdf.set_fill_color(52, 152, 219)
pdf.set_text_color(255, 255, 255)
pdf.cell(0, 10, 'PROJECT INFORMATION', ln=True, fill=True)
pdf.set_text_color(0, 0, 0)
pdf.set_font('helvetica', '', 11)
pdf.cell(0, 8, f'Project Key: anas4208-workspace_anas4208-workspace', ln=True)
pdf.cell(0, 8, f'Lines of Code: {metrics.get("ncloc", "N/A")}', ln=True)
pdf.cell(0, 8, f'Last Analysis: {datetime.now().strftime("%Y-%m-%d")}', ln=True)
pdf.ln(5)

# Quality Gate
pdf.set_font('helvetica', 'B', 12)
pdf.set_fill_color(46, 204, 113)
pdf.cell(0, 10, 'QUALITY GATE STATUS', ln=True, fill=True)
pdf.set_text_color(0, 0, 0)

coverage = float(metrics.get('coverage', 0))
if coverage >= 80:
    status = 'PASSED ✅'
    status_color = [46, 204, 113]
elif coverage >= 60:
    status = 'WARNING ⚠️'
    status_color = [241, 196, 15]
else:
    status = 'FAILED ❌'
    status_color = [231, 76, 60]

pdf.set_font('helvetica', 'B', 14)
pdf.set_fill_color(status_color[0], status_color[1], status_color[2])
pdf.cell(0, 10, f'Status: {status}', ln=True, align='C', fill=True)
pdf.ln(5)

# Coverage Metrics
pdf.set_font('helvetica', 'B', 12)
pdf.set_fill_color(52, 152, 219)
pdf.cell(0, 10, 'CODE COVERAGE METRICS', ln=True, fill=True)
pdf.set_font('helvetica', '', 11)
pdf.set_text_color(0, 0, 0)

pdf.cell(80, 8, 'Coverage:', border=1)
pdf.cell(40, 8, f'{metrics.get("coverage", "0")}%', border=1, align='C')
pdf.cell(60, 8, f'Target: 80%', border=1, align='C')
pdf.ln()

pdf.cell(80, 8, 'Lines to Cover:', border=1)
pdf.cell(100, 8, f'{metrics.get("lines_to_cover", "0")}', border=1)
pdf.ln()

pdf.cell(80, 8, 'Uncovered Lines:', border=1)
pdf.cell(100, 8, f'{metrics.get("uncovered_lines", "0")}', border=1)
pdf.ln()
pdf.ln(5)

# Issues Summary
pdf.set_font('helvetica', 'B', 12)
pdf.set_fill_color(231, 76, 60)
pdf.cell(0, 10, 'ISSUES SUMMARY', ln=True, fill=True)
pdf.set_font('helvetica', '', 11)

bugs = int(metrics.get('bugs', 0))
vulns = int(metrics.get('vulnerabilities', 0))
smells = int(metrics.get('code_smells', 0))

pdf.cell(60, 8, 'Bugs:', border=1)
pdf.cell(30, 8, str(bugs), border=1, align='C')
pdf.cell(90, 8, 'Critical: 0' if bugs == 0 else 'Needs Fix', border=1)
pdf.ln()

pdf.cell(60, 8, 'Vulnerabilities:', border=1)
pdf.cell(30, 8, str(vulns), border=1, align='C')
pdf.cell(90, 8, 'Critical: 0' if vulns == 0 else 'Needs Fix', border=1)
pdf.ln()

pdf.cell(60, 8, 'Code Smells:', border=1)
pdf.cell(30, 8, str(smells), border=1, align='C')
pdf.cell(90, 8, f'Total Issues: {len(issues)}', border=1)
pdf.ln()
pdf.ln(5)

# Ratings
pdf.set_font('helvetica', 'B', 12)
pdf.set_fill_color(155, 89, 182)
pdf.cell(0, 10, 'QUALITY RATINGS', ln=True, fill=True)
pdf.set_font('helvetica', '', 11)

rating_map = {'1.0': 'A (Excellent)', '2.0': 'B (Good)', '3.0': 'C (Average)', '4.0': 'D (Poor)', '5.0': 'E (Very Poor)'}

reliability = rating_map.get(metrics.get('reliability_rating', '1.0'), 'A')
security = rating_map.get(metrics.get('security_rating', '1.0'), 'A')
maintainability = rating_map.get(metrics.get('sqale_rating', '1.0'), 'A')

pdf.cell(80, 8, 'Reliability Rating:', border=1)
pdf.cell(100, 8, reliability, border=1)
pdf.ln()

pdf.cell(80, 8, 'Security Rating:', border=1)
pdf.cell(100, 8, security, border=1)
pdf.ln()

pdf.cell(80, 8, 'Maintainability Rating:', border=1)
pdf.cell(100, 8, maintainability, border=1)
pdf.ln()
pdf.ln(5)

# Duplications
pdf.set_font('helvetica', 'B', 12)
pdf.set_fill_color(241, 196, 15)
pdf.cell(0, 10, 'CODE DUPLICATIONS', ln=True, fill=True)
pdf.set_font('helvetica', '', 11)
pdf.cell(0, 8, f'Duplications: {metrics.get("duplicated_lines_density", "0")}% (Target: <10%)', ln=True)

if float(metrics.get('duplicated_lines_density', 0)) < 10:
    pdf.set_text_color(46, 204, 113)
    pdf.cell(0, 8, '✅ PASSED - Below threshold', ln=True)
else:
    pdf.set_text_color(231, 76, 60)
    pdf.cell(0, 8, '❌ FAILED - Above threshold', ln=True)

pdf.set_text_color(0, 0, 0)
pdf.ln(5)

# Issues List (top 10)
if issues:
    pdf.add_page()
    pdf.set_font('helvetica', 'B', 12)
    pdf.set_fill_color(231, 76, 60)
    pdf.cell(0, 10, 'OPEN ISSUES DETAILS', ln=True, fill=True)
    pdf.ln(5)
    
    pdf.set_font('helvetica', 'B', 9)
    pdf.cell(15, 7, '#', border=1, align='C')
    pdf.cell(25, 7, 'Severity', border=1, align='C')
    pdf.cell(50, 7, 'File', border=1, align='C')
    pdf.cell(100, 7, 'Description', border=1, align='C')
    pdf.ln()
    
    pdf.set_font('helvetica', '', 8)
    for i, issue in enumerate(issues[:10], 1):
        severity = issue.get('severity', 'INFO')
        component = issue.get('component', 'Unknown').split(':')[-1][:30]
        message = issue.get('message', '')[:60]
        
        pdf.cell(15, 6, str(i), border=1, align='C')
        pdf.cell(25, 6, severity, border=1, align='C')
        pdf.cell(50, 6, component, border=1)
        pdf.multi_cell(100, 6, message, border=1)
    
    if len(issues) > 10:
        pdf.cell(0, 8, f'... and {len(issues) - 10} more issues', ln=True, align='R')

# Save
pdf.output('SonarCloud_Quality_Report.pdf')
print('✅ PDF GENERATED: SonarCloud_Quality_Report.pdf')
print(f'📊 Coverage: {metrics.get("coverage", "0")}%')
print(f'🐛 Bugs: {bugs}')
print(f'🔒 Vulnerabilities: {vulns}')
print(f'💨 Code Smells: {smells}')
print(f'📈 Duplications: {metrics.get("duplicated_lines_density", "0")}%')
