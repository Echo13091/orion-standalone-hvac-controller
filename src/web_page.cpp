#include "web_page.h"

String htmlPage() {
  return R"HTML(
<!doctype html>
<html>
<head>
  <meta charset="utf-8">
  <title>Orion Standalone HVAC</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <style>
    body { margin:0; padding:20px; background:#050505; color:#f5f5f5; font-family:Arial,sans-serif; }
    .wrap { max-width:720px; margin:0 auto; }
    .card { background:#121212; border:1px solid #2a2a2a; border-radius:14px; padding:16px; margin:14px 0; }
    .muted { color:#aaa; font-size:13px; }
    pre { background:#080808; border:1px solid #222; border-radius:10px; padding:12px; white-space:pre-wrap; word-break:break-word; }
  </style>
</head>
<body>
  <div class="wrap">
    <h1>Orion Standalone HVAC</h1>
    <div class="muted">ESP32-S3 local HVAC controller</div>
    <div class="card">
      <h2>Status</h2>
      <pre id="status">Loading...</pre>
    </div>
  </div>

<script>
async function refreshStatus() {
  try {
    const res = await fetch('/api/status');
    const data = await res.json();
    document.getElementById('status').textContent = JSON.stringify(data, null, 2);
  } catch (err) {
    document.getElementById('status').textContent = String(err);
  }
}
setInterval(refreshStatus, 3000);
refreshStatus();
</script>
</body>
</html>
)HTML";
}
