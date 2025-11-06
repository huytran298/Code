import math
from collections import defaultdict
import numpy as np
class mariscotti :
    def __init__(self, N, z : int, w : int):
        self.N = N
        self.z = z
        self.w = w
        self.m = int((w - 1) / 2)
        self.C_coeffs = self.C()
        self.mariscotti_calc()
        
        self.peak_finding_procedure()
    def C(self):
        C_current = defaultdict(int)
        C_current[0] = -2
        C_current[1] = 1
        C_current[-1] = 1
        for current_z in range(1, self.z + 1):
            C_next = defaultdict(int)
            
            # Xác định phạm vi của k. 
            # Phạm vi của C(z) là (z*m + 1)
            max_k_reach = current_z * self.m + 1
            
            for k in range(-max_k_reach, max_k_reach + 1):
                sum_c = 0
                # Áp dụng công thức (9):
                # C_k(z) = sum( C_{k-p}(z-1) ) for p in [-m, m]
                for p in range(-self.m, self.m + 1):
                    k_prime = k - p
                    sum_c += C_current[k_prime]
                
                C_next[k] = sum_c
            
            # Cập nhật C cho vòng lặp z tiếp theo
            C_current = C_next
            
        # Trả về bộ hệ số cuối cùng (cho z = self.z)
        return C_current
    def mariscotti_calc(self):
        
        z = self.z
        m = self.m
        N = self.N
        S = []
        F = []
        for i in range(0, len(N)):
            boundary = int(z * m + 1)
            start = int(max(i - boundary, 0))
            end = int(min(i + boundary + 1, len(N)))
            sum_S = 0
            sum_F = 0
            for j in range (start, end) :
                C = self.C_coeffs[j - i]
                sum_S += C * int(N[j])
                sum_F += (C ** 2) * int(N[j])
            S.append(sum_S)
            F.append(math.sqrt(max(0, sum_F)))
        # n1 = 1.22 * 0.6 * w
        self.S = S
        self.F = F
    def peak_finding_procedure(self):
        S = self.S
        F = self.F
        w = self.w
        i = [i for i in range(6)]
        gamma = self.w / 0.6  # Ước tính FWHM từ w 
        k_z = 1.22             # Hệ số từ Hình 8 [cite: 443]
        n1 = int((k_z * gamma) + 0.5) # Phương trình (18)
        peak_pos = []
        M = 0
        for idx in range(1, len(S)):
            
            if S[idx] > F[idx]:
                M = 1
            elif S[idx] > 0:
                M = 2
            else :
                M = 3
            if S[idx - 1] > F[idx - 1]:
                if M == 3:
                    
                    i[3] = idx
                elif M == 1:
                    continue
                i[2] = idx - 1
            elif S[idx - 1] > 0:
                if M == 3:
                    i[3] = idx
                elif M == 1:
                    i[1] = idx
            else :
                if M == 3 :
                    continue
                i[5] = idx - 1
                tmp = S[i[3]]
                i[4] = i[3]
                for j in range(i[3], idx):
                    if tmp > S[j]:
                        i[4] = j
                        tmp = S[j]
                
                n2 = abs((F[i[4]] / S[i[4]]) * 1 / 2 * (n1 + 2) + 0.5)
                n2 = n2 if n2 >= 1 else 0

                n3 = abs((n1 + 2) * (1 - 2 * (F[i[4]] / S[i[4]])) + 1 / 2)  
                if abs(S[i[4]]) > 2 * F[i[4]] and abs((i[5] - i[3] + 1) - n1) <= 2 and i[3] - i[2] - 1 <= n2 and i[2] - i[1] + 1 >= n3:
                    peak_pos.append(i[4])
        self.peak_pos = peak_pos
        return peak_pos
    def peak_fitting_procedure(self):
        peak_pos = self.peak_pos
        N = self.N
        for i in range(0, len(peak_pos)) : 
            FWHM = 0
            limitFWHM = 50
            
            while FWHM <= limitFWHM :  
                FWHM += 2
                p = [0 for i in range(0, 9)]
                iMin = peak_pos[i] - 5 * FWHM
                iMax = peak_pos[i] + 5 * FWHM

                if i < len(peak_pos) - 1 and peak_pos[i + 1] < iMax :
                    p[4] = N[peak_pos[i + 1]] - p[6]
                    pass
                









        

