import math
from collections import defaultdict
import numpy as np
from scipy.optimize import least_squares

class mariscotti:
    def __init__(self, N, z: int, w: int):
        # [QUAN TRỌNG] Ép kiểu sang float để tránh lỗi tràn số (Overflow)
        self.N = np.array(N, dtype=float)
        self.z = z
        self.w = w
        self.m = int((w - 1) / 2)
        
        # Khởi tạo danh sách lưu kết quả các bước tìm đỉnh
        # i[1]..i[6] tương ứng với các biến trong bài báo
        self.i = {k: [] for k in range(1, 7)}
        
        self.C_coeffs = self.C()
        self.fitted_params_list = []
        self.peak_pos = []
        
        # Chạy tính toán
        self.mariscotti_calc()
        self.peak_finding_procedure()
        
        # Chỉ chạy fitting nếu tìm thấy đỉnh
        if len(self.peak_pos) > 0:
            print(f"Phát hiện {len(self.peak_pos)} đỉnh. Bắt đầu fitting...")
            self.peak_fitting_procedure()
        else:
            print("Không tìm thấy đỉnh nào.")

    def C(self):
        C_current = defaultdict(int)
        C_current[0] = -2
        C_current[1] = 1
        C_current[-1] = 1
        for current_z in range(1, self.z + 1):
            C_next = defaultdict(int)
            max_k_reach = current_z * self.m + 1
            for k in range(-max_k_reach, max_k_reach + 1):
                sum_c = 0
                for p in range(-self.m, self.m + 1):
                    k_prime = k - p
                    sum_c += C_current[k_prime]
                C_next[k] = sum_c
            C_current = C_next
        return C_current

    def mariscotti_calc(self):
        z = self.z
        m = self.m
        N = self.N
        S = []
        F = []
        
        # Tính S và F
        for i in range(0, len(N)):
            boundary = int(z * m + 1)
            start = int(max(i - boundary, 0))
            end = int(min(i + boundary + 1, len(N)))
            
            sum_S = 0.0
            sum_F = 0.0
            for j in range(start, end):
                # Sử dụng .get() để an toàn nếu index lệch
                C_val = self.C_coeffs[j - i]
                if C_val == 0: continue
                
                val = N[j]
                sum_S += C_val * val
                sum_F += (C_val ** 2) * val
                
            S.append(sum_S)
            F.append(math.sqrt(max(0, sum_F)))
            
        self.S = np.array(S)
        self.F = np.array(F)

    def peak_finding_procedure(self):
        S = self.S
        F = self.F
        gamma = self.w / 0.6
        k_z = 1.22
        n1 = int((k_z * gamma) + 0.5)
        
        peak_pos_list = []
        
        # Biến tạm lưu trạng thái đỉnh hiện tại
        curr_i = {}
        M = 0
        st = False
        tmp = 0
        
        for idx in range(1, len(S) - 1):
            if S[idx] > F[idx] and S[idx - 1] <= F[idx - 1]:
                curr_i[1] = idx
                st = True
                M = 1
                tmp = 0
                
            if st:
                if M == 1 and S[idx] >= F[idx]:
                    curr_i[2] = idx
                elif M == 1:
                    M = 2
                    
                if M == 2:
                    if S[idx] < 0:
                        curr_i[3] = idx
                        tmp = S[idx]
                        curr_i[4] = idx
                        M = 3
                    continue
                if M == 3:
                    curr_i[5] = idx
                    if tmp >= S[idx]:
                        tmp = S[idx]
                        curr_i[4] = idx     
                    if S[idx + 1] >= 0:
                        st = False
                        M = 0
                        
                        i4 = curr_i.get(4, 0)
                        if abs(S[i4]) <= 2 * F[i4]: 
                            continue
                        
                        i5, i3 = curr_i.get(5), curr_i.get(3)
                        if abs(i5 - i3 + 1 - n1) > 2: 
                            continue
                        
                        val_ratio = F[i4] / S[i4] if S[i4] != 0 else 0
                        n2 = abs(val_ratio * 0.5 * (n1 + 2) + 0.5)
                        n2 = max(1, n2)
                        
                        i2 = curr_i.get(2)
                        if i3 - i2 - 1 > n2: 
                            continue
                        
                        n3 = abs((n1 - 2) * (1 - 2 * val_ratio) + 0.5)
                        n3_1 = abs((n1 + 2) * (1 - 2 * val_ratio) + 0.5)
                        n3_min = min(n3, n3_1)
                        
                        i1 = curr_i.get(1)
                        if i2 - i1 + 1 < n3_min: 
                            continue
                        
                        # Tính trọng tâm i0 (i[6])
                        tmp_sum = 0
                        tmp_prod = 0
                        for j in range(i3, i5 + 1):
                            if j < len(S):
                                tmp_sum += S[j]
                                tmp_prod += j * S[j]
                        
                        if tmp_sum != 0:
                            curr_i[6] = tmp_prod / tmp_sum
                            # Lưu kết quả
                            for k in range(1, 7):
                                self.i[k].append(curr_i.get(k, 0))
                            peak_pos_list.append(i4)
                        continue
        
        self.peak_pos = peak_pos_list

    def calculate_t(self, p, x, pos_idx, width_idx):
        width = p[width_idx] if p[width_idx] > 1e-5 else 1e-5
        return 1.665 * (x - p[pos_idx]) / width

    def f_model(self, p, x):
        x = np.array(x)
        t1 = self.calculate_t(p, x, 1, 2)
        y = p[0] * np.exp(-t1 ** 2)
        
        # Doublet
        if p[3] > 0: 
            t2 = self.calculate_t(p, x, 4, 2)
            y += p[3] * np.exp(-t2 ** 2)
            
        y += p[5] + p[6] * x + p[7] * (x ** 2)
        return y

    def residuals(self, p, x_roi, y_roi):
        y_model = self.f_model(p, x_roi)
        # Weights = sqrt(y). Thêm eps để tránh chia 0
        weights = np.sqrt(np.maximum(y_roi, 1.0))
        return (y_model - y_roi) / weights

    def peak_fitting_procedure(self):
        peak_pos = self.peak_pos
        N = self.N
        
        i = 0
        while i < len(peak_pos):
            current_idx = i
            center_est = self.i[6][current_idx]
            
            FWHM = 0.0
            limitFWHM = 50.0
            fit_success = False
            
            # Vòng lặp tăng FWHM
            while FWHM <= limitFWHM:
                FWHM += 2.0
                
                # Cắt vùng ROI
                min_i = int(max(0, center_est - 5 * FWHM))
                max_i = int(min(len(N), center_est + 5 * FWHM))
                
                x_data = np.arange(min_i, max_i)
                y_data = N[min_i:max_i]
                
                if len(x_data) < 5: continue
                
                # --- KHỞI TẠO THAM SỐ (FIX LỖI BOUNDS) ---
                p = np.zeros(8)
                
                # Ước lượng nền
                l = 1
                idx_L = int(peak_pos[current_idx])
                left_bg_idx = max(0, idx_L - int(5*FWHM))
                right_bg_idx = min(len(N)-1, idx_L + int(5*FWHM))
                
                bg_left = np.mean(N[max(0, left_bg_idx-l):min(len(N), left_bg_idx+l+1)])
                bg_right = np.mean(N[max(0, right_bg_idx-l):min(len(N), right_bg_idx+l+1)])
                range_len = max(1, right_bg_idx - left_bg_idx)
                
                p[6] = (bg_right - bg_left) / range_len # Slope
                p[5] = bg_left - p[6] * left_bg_idx     # Intercept
                
                # Tính nền tại đỉnh để ước lượng Amp
                bg_at_peak = p[5] + p[6] * center_est
                
                p[1] = center_est
                p[2] = FWHM
                p[0] = max(N[int(center_est)] - bg_at_peak, 10.0) # Amp1 > 0
                
                # [QUAN TRỌNG] Gán giá trị hợp lệ cho p[4] (Pos2) ngay cả khi không dùng
                # Để tránh lỗi "Initial guess outside bounds" vì bounds của p[4] là [min_i, max_i]
                p[4] = center_est 
                
                is_doublet = False
                skip_next = False
                
                if current_idx + 1 < len(peak_pos):
                    next_peak_loc = self.i[6][current_idx + 1]
                    if next_peak_loc < max_i:
                        is_doublet = True
                        bg_at_next = p[5] + p[6] * next_peak_loc
                        p[3] = max(N[int(next_peak_loc)] - bg_at_next, 10.0)
                        p[4] = next_peak_loc # Cập nhật lại nếu là Doublet thật
                        skip_next = True
                
                # Bounds: Amp1, Pos1, Width, Amp2, Pos2, Bg0, Bg1, Bg2
                lower_bounds = [0, min_i, 0.1, 0, min_i, -np.inf, -np.inf, -np.inf]
                upper_bounds = [np.inf, max_i, np.inf, np.inf, max_i, np.inf, np.inf, np.inf]
                
                try:
                    res = least_squares(
                        self.residuals, 
                        p, 
                        args=(x_data, y_data),
                        bounds=(lower_bounds, upper_bounds)
                    )
                    
                    if res.success:
                        self.fitted_params_list.append({
                            'roi_x': x_data,
                            'params': res.x,
                            'is_doublet': is_doublet
                        })
                        fit_success = True
                        if skip_next: i += 1
                        break
                        
                except ValueError:
                    pass # Bỏ qua lỗi để thử FWHM khác hoặc đỉnh khác

            if not fit_success:
                print(f"Bỏ qua đỉnh tại {center_est:.1f} (không hội tụ).")
            
            i += 1
    def plot_results(self):
        try:
            import matplotlib.pyplot as plt
        except ImportError:
            print("Cần thư viện matplotlib để vẽ biểu đồ (pip install matplotlib)")
            return

        plt.figure(figsize=(14, 7))
        
        # 1. Vẽ dữ liệu gốc (Raw Data)
        # Vẽ chấm nhỏ màu xám để làm nền
        x_all = np.arange(len(self.N))
        plt.scatter(x_all, self.N, s=3, color='gray', alpha=0.4, label='Dữ liệu gốc (Observed)')
        
        # 2. Duyệt qua danh sách các đỉnh đã fit để vẽ đường cong
        print(f"Đang vẽ {len(self.fitted_params_list)} đường cong fit...")
        
        for i, item in enumerate(self.fitted_params_list):
            x_roi = item['roi_x']   # Vùng kênh (ROI)
            p = item['params']      # Tham số tối ưu (res.x)
            
            # Tính toán lại đường cong y theo mô hình
            y_fit = self.f_model(p, x_roi)
            
            # Vẽ đường fit (Chỉ thêm label cho đường đầu tiên để Legend không bị lặp)
            label = 'Đường Fit (Model)' if i == 0 else None
            plt.plot(x_roi, y_fit, color='red', linewidth=1.5, label=label)
            
            # (Tùy chọn) Vẽ đường thẳng đánh dấu vị trí đỉnh
            plt.axvline(x=p[1], color='blue', linestyle='--', linewidth=0.5, alpha=0.5)
            if item['is_doublet']:
                 plt.axvline(x=p[4], color='blue', linestyle='--', linewidth=0.5, alpha=0.5)

        plt.title(f"Kết quả Fitting Mariscotti - {len(self.fitted_params_list)} đỉnh được tìm thấy")
        plt.xlabel("Kênh (Channel)")
        plt.ylabel("Số đếm (Counts)")
        plt.legend()
        plt.grid(True, alpha=0.3)
        plt.show()