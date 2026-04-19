import json
import urllib.request
import base64
import ssl
from fpdf import FPDF

def fetch_metrics():
    url = "https://sonarcloud.io/api/measures/component?component=anas4208-workspace_anas4208-workspace&metricKeys=bugs,vulnerabilities,code_smells,coverage,duplicated_lines_density,ncloc,reliability_rating,security_rating,sqale_rating"
    token = "6ffccf5176f47d66e243063b34d92d681c11df80:"
    
    b64_token = base64.b64encode(token.encode('utf-8')).decode('utf-8')
    req = urllib.request.Request(url)
    req.add_header("Authorization", f"Basic {b64_token}")

    # Bypass macOS SSL certificate verification
    ctx = ssl.create_default_context()
    ctx.check_hostname = False
    ctx.verify_mode = ssl.CERT_NONE

    try:
        with urllib.request.urlopen(req, context=ctx) as response:
            data = json.loads(response.read().decode())
            return data.get('component', {}).get('measures', [])
    except Exception as e:
        print(f"Error fetching data from API: {e}")
        return []

class PDF(FPDF):
    def header(self):
        self.set_font('helvetica', 'B', 16)
        self.cell(0, 10, 'Phase 1: SonarCloud Dashboard Analysis', align='C', ln=True)
        self.line(10, 20, 200, 20)
        self.ln(10)

def generate_report():
    measures = fetch_metrics()
    if not measures:
        print("Failed to pull metrics. Exiting.")
        return

    metrics = {m['metric']: m['value'] for m in measures}
    rating_map = {'1.0': 'A', '2.0': 'B', '3.0': 'C', '4.0': 'D', '5.0': 'E'}

    pdf = PDF()
    pdf.add_page()

    pdf.set_font('helvetica', 'B', 14)
    pdf.cell(0, 10, "Project Scope", ln=True)
    pdf.set_font('helvetica', '', 12)
    pdf.cell(0, 8, f"Lines of Code (NCLOC): {metrics.get('ncloc', '0')}", ln=True)
    pdf.ln(5)

    pdf.set_font('helvetica', 'B', 14)
    pdf.cell(0, 10, "Discovered Issues", ln=True)
    pdf.set_font('helvetica', '', 12)
    pdf.cell(0, 8, f"Bugs: {metrics.get('bugs', '0')}", ln=True)
    pdf.cell(0, 8, f"Vulnerabilities: {metrics.get('vulnerabilities', '0')}", ln=True)
    pdf.cell(0, 8, f"Code Smells: {metrics.get('code_smells', '0')}", ln=True)
    pdf.ln(5)

    pdf.set_font('helvetica', 'B', 14)
    pdf.cell(0, 10, "Health Metrics", ln=True)
    pdf.set_font('helvetica', '', 12)
    pdf.cell(0, 8, f"Coverage: {metrics.get('coverage', '0.0')}%", ln=True)
    pdf.cell(0, 8, f"Duplications: {metrics.get('duplicated_lines_density', '0.0')}%", ln=True)
    pdf.ln(5)

    pdf.set_font('helvetica', 'B', 14)
    pdf.cell(0, 10, "Quality Gate Ratings", ln=True)
    pdf.set_font('helvetica', '', 12)
    
    rel = rating_map.get(metrics.get('reliability_rating', '1.0'), 'N/A')
    sec = rating_map.get(metrics.get('security_rating', '1.0'), 'N/A')
    maint = rating_map.get(metrics.get('sqale_rating', '1.0'), 'N/A')

    pdf.cell(0, 8, f"Reliability Rating: {rel}", ln=True)
    pdf.cell(0, 8, f"Security Rating: {sec}", ln=True)
    pdf.cell(0, 8, f"Maintainability Rating: {maint}", ln=True)

    pdf.output('SonarCloud_Analysis_Metrics.pdf')
    print("SUCCESS: Generated SonarCloud_Analysis_Metrics.pdf")

if __name__ == "__main__":
    generate_report()
