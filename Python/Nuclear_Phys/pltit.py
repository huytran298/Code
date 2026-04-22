import argparse
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np


def main() -> None:
	parser = argparse.ArgumentParser(
		description="Read S and F columns from a data file and plot them together."
	)
	parser.add_argument(
		"file",
		nargs="?",
		default="C:\\Users\\huyhuyne\\Documents\\Code\\Python\\Nuclear_Phys\\MariscottiData_20260402_135337.txt",
		help="Path to the data file (default: %(default)s)",
	)
	args = parser.parse_args()

	file_path = Path(args.file)
	if not file_path.exists():
		raise FileNotFoundError(f"File not found: {file_path}")

	# File format: header line then columns N, S, F separated by whitespace or tabs.
	data = np.loadtxt(file_path, skiprows=1)
	if data.ndim == 1 or data.shape[1] < 3:
		raise ValueError("Expected at least 3 columns: N, S, F")

	s = data[:, 1]
	f = data[:, 2]
	x = np.arange(len(s))

	plt.figure(figsize=(10, 5))
	plt.plot(x, s, label="S", linewidth=1.2)
	plt.plot(x, f, label="F", linewidth=1.2)
	plt.xlabel("Index")
	plt.ylabel("Value")
	plt.title("S and F vs Index")
	plt.grid(True, alpha=0.3)
	plt.legend()
	plt.tight_layout()
	plt.show()


if __name__ == "__main__":
	main()
