import numpy as np

class MariscottiAlgorithm:
    """
    Mariscotti's method for peak search and energy calibration in gamma-ray spectra.
    Based on the classic 1967 paper on automatic peak location.
    """
    
    def __init__(self, spectrum, smoothing_width=5, second_diff_width=3):
        """
        Initialize the Mariscotti algorithm.
        
        Parameters:
        -----------
        spectrum : array-like
            The input gamma-ray spectrum (counts per channel)
        smoothing_width : int
            Width parameter for smoothing (m1 in original paper)
        second_diff_width : int
            Width parameter for second difference (m2 in original paper)
        """
        self.spectrum = np.array(spectrum, dtype=float)
        self.m1 = smoothing_width
        self.m2 = second_diff_width
        self.smoothed_spectrum = None
        self.second_difference = None
        self.peaks = []
        
    def smooth(self):
        """
        Apply smoothing to the spectrum using moving average.
        S(i) = sum of counts over width 2*m1+1
        """
        n = len(self.spectrum)
        self.smoothed_spectrum = np.zeros(n)
        
        for i in range(n):
            start = max(0, i - self.m1)
            end = min(n, i + self.m1 + 1)
            self.smoothed_spectrum[i] = np.sum(self.spectrum[start:end])
            
        return self.smoothed_spectrum
    
    def compute_second_difference(self):
        """
        Compute the second difference of the smoothed spectrum.
        D(i) = S(i-m2) - 2*S(i) + S(i+m2)
        """
        if self.smoothed_spectrum is None:
            self.smooth()
            
        n = len(self.smoothed_spectrum)
        self.second_difference = np.zeros(n)
        
        for i in range(self.m2, n - self.m2):
            self.second_difference[i] = (
                self.smoothed_spectrum[i - self.m2] 
                - 2 * self.smoothed_spectrum[i] 
                + self.smoothed_spectrum[i + self.m2]
            )
            
        return self.second_difference
    
    def find_peaks(self, threshold=None, sensitivity=3.0):
        """
        Locate peaks using the second difference method.
        
        Parameters:
        -----------
        threshold : float, optional
            Absolute threshold for peak detection. If None, use statistical threshold
        sensitivity : float
            Sensitivity parameter (number of standard deviations)
            
        Returns:
        --------
        peaks : list of int
            Channel numbers where peaks are located
        """
        if self.second_difference is None:
            self.compute_second_difference()
            
        # Calculate threshold if not provided
        if threshold is None:
            # Use standard deviation of second difference in "quiet" regions
            std_dev = np.std(self.second_difference[self.second_difference < 0])
            threshold = -sensitivity * std_dev
        
        self.peaks = []
        n = len(self.second_difference)
        
        # Find local minima in second difference (peaks in original spectrum)
        for i in range(self.m2 + 1, n - self.m2 - 1):
            if self.second_difference[i] < threshold:
                # Check if it's a local minimum
                if (self.second_difference[i] < self.second_difference[i-1] and 
                    self.second_difference[i] < self.second_difference[i+1]):
                    self.peaks.append(i)
                    
        return self.peaks
    
    def get_peak_properties(self, peak_channel):
        """
        Extract peak properties (position, height, approximate width).
        
        Parameters:
        -----------
        peak_channel : int
            Channel number of the peak
            
        Returns:
        --------
        dict : Peak properties
        """
        height = self.spectrum[peak_channel]
        
        # Estimate FWHM by finding half-maximum points
        half_max = height / 2.0
        
        # Search left
        left = peak_channel
        while left > 0 and self.spectrum[left] > half_max:
            left -= 1
            
        # Search right
        right = peak_channel
        while right < len(self.spectrum) - 1 and self.spectrum[right] > half_max:
            right += 1
            
        fwhm = right - left
        
        return {
            'channel': peak_channel,
            'height': height,
            'fwhm': fwhm,
            'second_diff_value': self.second_difference[peak_channel]
        }
    
    def analyze(self, threshold=None, sensitivity=3.0):
        """
        Perform complete peak analysis.
        
        Returns:
        --------
        list of dict : Properties of all detected peaks
        """
        self.find_peaks(threshold, sensitivity)
        
        peak_properties = []
        for peak in self.peaks:
            props = self.get_peak_properties(peak)
            peak_properties.append(props)
            
        return peak_properties