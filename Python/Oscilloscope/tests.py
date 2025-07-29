import requests
import json
import re

BASE_HOST = "http://192.168.0.152"
CMD_URL   = BASE_HOST + "/command"
PAGEID    = 0

# 1) Tạo session và lấy cookie giống browser
sess = requests.Session()
sess.get(BASE_HOST + "/")

# 2) Mở một HTTP GET dài (long‐poll / SSE)
resp = sess.get(
    CMD_URL,
    params={"commandText": "",    # blank để polling trạng thái
            "PAGEID": PAGEID},
    headers={
        "Accept": "text/event-stream",         # yêu cầu SSE
        "X-Requested-With": "XMLHttpRequest",
        "Referer": BASE_HOST + "/",
    },
    stream=True,
    timeout=5
)

# 3) Đọc từng dòng SSE, tìm “data: …”
for raw in resp.iter_lines(decode_unicode=True):
    if not raw or not raw.startswith("data:"):
        continue
    # Lấy payload JSON sau “data:”
    payload = raw[len("data:"):].strip()
    try:
        doc = json.loads(payload)
    except json.JSONDecodeError:
        continue

    # Thử lấy MPos từ JSON
    mpos = doc.get("MPos") or doc.get("mpos") or doc.get("pos")
    if mpos:
        x, y, z = map(float, mpos.split(","))
        print(f"📍 Current position → X={x:.3f}, Y={y:.3f}, Z={z:.3f}")
        break

resp.close()
