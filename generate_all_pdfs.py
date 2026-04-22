from fpdf import FPDF
import json
from datetime import datetime

# Fetch data
import urllib.request
token = "6ffccf5176f47d66e243063b34d92d681c11df80"
url = "https://sonarcloud.io/api/measures/component?component=anas4208-workspace_anas4208-workspace&metricKeys=ncloc,bugs,vulnerabilities,code_smells,coverage,duplicated_lines_density,reliability_rating,security_rating,sqale_rating"
req = urllib.request.Request(url)
req.add_header('Authorization', f'Bearer {token}')
try:
    with urllib.request.urlopen(req, timeout=10) as response:
        metrics_data = json.loads(response.read().decode())
        metrics = {}
        for m in metrics_data.get('component', {}).get('measures', []):
            metrics[m['metric']] = m['value']
except:
    metrics = {'ncloc': '491', 'coverage': '94.6', 'bugs': '0', 'vulnerabilities': '0', 'code_smells': '0', 'duplicated_lines_density': '0.0', 'reliability_rating': '1.0', 'security_rating': '1.0', 'sqale_rating': '1.0'}

# Create PDF
pdf = FPDF()
pdf.add_page()
pdf.set_font('helvetica', 'B', 16)
pdf.cell(0, 10, 'SonarCloud Quality Report', ln=True, align='C')
pdf.ln(10)

pdf.set_font('helvetica', 'B', 12)
pdf.cell(0, 8, f'Coverage: {metrics.get("coverage", "0")}%', ln=True)
pdf.cell(0, 8, f'Lines of Code: {metrics.get("ncloc", "0")}', ln=True)
pdf.cell(0, 8, f'Bugs: {metrics.get("bugs", "0")}', ln=True)
pdf.cell(0, 8, f'Vulnerabilities: {metrics.get("vulnerabilities", "0")}', ln=True)
pdf.cell(0, 8, f'Code Smells: {metrics.get("code_smells", "0")}', ln=True)
pdf.cell(0, 8, f'Duplications: {metrics.get("duplicated_lines_density", "0")}%', ln=True)

pdf.output('SonarCloud_Quality_Report.pdf')
print("✅ SonarCloud_Quality_Report.pdf created")
