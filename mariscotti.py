import math
from collections import defaultdict
import numpy as np
class mariscotti :
    def __init__(self, N, z : int, w : int):
        self.N = N
        self.z = z
        self.w = w
        self.m = int((w - 1) / 2)
        self.i = [[], [], [], [], [], []]
        self.i[1] = []
        self.i[2] = []
        self.i[3] = []
        self.i[4] = []
        self.i[5] = []
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
        st = False
        tmp = 0
        for idx in range(1, len(S) - 1):
            if S[idx] > F[idx] and S[idx - 1] <= F[idx - 1]:
                i[1] = idx
                st = True
                M = 1
                tmp = 0
                
            if st :
                if M == 1 and S[idx] >= F[idx]:
                    i[2] = idx
                elif M == 1:
                    M = 2
                    
                if M == 2:
                    if S[idx] < 0:
                        i[3] = idx
                        tmp = S[idx]
                        
                        i[4] = idx
                        M = 3
                    continue
                if M == 3:
                    
                    i[5] = idx
                    if tmp >= S[idx] :
                        tmp = S[idx]
                        i[4] = idx     
                    if S[idx + 1] >= 0 :
                        st = False
                        M = 0
                        #print(f'i4 : {i[4]}')
                        
                        
                        
                        #first codition (14)
                        if abs(S[i[4]]) <= 2 * F[i[4]] :
                            continue
                        #second codition (18)
                        if abs(i[5] - i[3] + 1 - n1) > 2:
                            continue
                        #third codition (21)
                        n2 = abs((F[i[4]] / S[i[4]]) * 0.5 * (n1 + 2) + 0.5)
                        n2 = n2 if n2 >= 1 else 1
                        if i[3] - i[2] - 1 > n2:
                            continue
                        #fourth codition (23)
                        n3 = abs((n1 - 2) * (1 - 2 * F[i[4]]/S[i[4]]) + 0.5)
                        if i[2] - i[1] + 1 < n3 :
                            continue
                        for k in range(1, 6) :
                            self.i[k].append(i[k])
                        peak_pos.append(i[4])
                        continue
                                       
        self.peak_pos = peak_pos
    def peak_fitting_procedure(self):
        peak_pos = self.peak_pos
        N = self.N
        l = 1

        preSum = [0] * len(N)
        preSum[0] = N[0]
        
        for i in range(1, len(N)):
            preSum[i] = preSum[i - 1] + N[i]
        
        for i in range(0, len(peak_pos) - 1) : 
            FWHM = 0
            limitFWHM = 50
            
            while FWHM <= limitFWHM :  
                FWHM += 2
                p = [0 for i in range(0, 9)]
                iMin = peak_pos[i] - 5 * FWHM
                iMax = peak_pos[i] + 5 * FWHM

                p[6] = (preSum[iMin + l] - preSum[iMin - l - 1] + preSum[iMax + l] - preSum[iMax - l - 1]) / (4 * l + 2)
                p[7] = (preSum[iMin + l] - preSum[iMin - l - 1] - (preSum[iMax + l] - preSum[iMax - l - 1])) / ((2 * l + 2) * (iMax - iMin + 1))
                p[1] = peak_pos[i + 1]
                p[2] = i
                p[3] = FWHM
                
                if i < len(peak_pos) - 1 and peak_pos[i + 1] < iMax :
                    p[4] = N[peak_pos[i + 1]] - p[6]
                    pass
                else :

                    p[4] = 0
                p[8] = 0








        

