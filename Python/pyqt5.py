import numpy as np
from PIL import Image, ImageDraw, ImageFont
from moviepy.editor import VideoClip

# Thông số video
duration = 5  # thời lượng video (giây)
fps = 24      # số khung hình trên giây
video_w, video_h = 2560, 1600  # kích thước khung video (MacBook Air M1)
bg_path = '../anime_physics_background.png'  # thay bằng đường dẫn đến file PNG bạn đã lưu
output_path = '../physics_anime.mov'  # nơi lưu file MOV đầu ra

# Load ảnh nền và resize về đúng kích thước
bg_img = Image.open(bg_path).convert('RGB')
bg_img = bg_img.resize((video_w, video_h), Image.ANTIALIAS)

# Load font hệ thống (đường dẫn có thể khác tùy OS)
# Ví dụ trên Ubuntu/Mac có thể là 'DejaVuSans-Bold.ttf'
font_path = '/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf'
font1 = ImageFont.truetype(font_path, 100)  # chữ "E=mc²"
font2 = ImageFont.truetype(font_path, 120)  # chữ "Ψ"

# Nội dung chữ chạy
text1 = "E=mc²"
text2 = "Ψ"

# Tính kích thước của từng đoạn text để tính toán vị trí di chuyển
dummy_img = Image.new('RGB', (1, 1))
draw_dummy = ImageDraw.Draw(dummy_img)
text1_w, text1_h = draw_dummy.textsize(text1, font=font1)
text2_w, text2_h = draw_dummy.textsize(text2, font=font2)

# Hàm vẽ khung hình tại thời điểm t (t tính bằng giây)
def make_frame(t):
    frame = bg_img.copy().convert('RGBA')
    draw = ImageDraw.Draw(frame)
    # Chữ "E=mc²" di chuyển từ trái sang phải
    x1 = -text1_w + (video_w + text1_w) * (t / duration)
    y1 = int(video_h * 0.2)
    draw.text((x1, y1), text1, font=font1, fill=(255, 255, 255, 255))
    # Chữ "Ψ" di chuyển từ trên xuống dưới
    x2 = int(video_w * 0.7)
    y2 = -text2_h + (video_h + text2_h) * (t / duration)
    draw.text((x2, y2), text2, font=font2, fill=(0, 255, 255, 255))
    return np.array(frame.convert('RGB'))

# Tạo VideoClip và thiết lập fps
video_clip = VideoClip(make_frame, duration=duration)
video_clip = video_clip.set_fps(fps)

# Xuất file MOV (2560×1600, 5 giây, chữ bay)
video_clip.write_videofile(
    output_path,
    codec="libx264",
    fps=fps,
    audio=False,
    preset="medium",
    ffmpeg_params=["-pix_fmt", "yuv420p"]
)
