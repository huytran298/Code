import sys
from pathlib import Path
import matplotlib.pyplot as plt
import math

def parse_cnf_txt(file_path: Path):
    energies = []
    counts = []

    in_channel_section = False
    header_skipped = False

    with file_path.open("r", encoding="utf-8", errors="ignore") as f:
        for line in f:
            line = line.strip()

            # Find start of channel data section
            if not in_channel_section:
                if line.startswith("# Channel data"):
                    in_channel_section = True
                    header_skipped = False  # next lines will be headers to skip
                continue

            # Skip the header lines right after "# Channel data"
            if in_channel_section and not header_skipped:
                # Expect two lines: column headers and dashed separator
                header_skipped = True  # this marks we saw the header title
                next(f, None)          # skip dashed separator line
                continue

            # Stop if we hit another comment block (unlikely in this file)
            if line.startswith("#") or not line:
                # allow blank lines; continue reading
                if not line:
                    continue

            # Parse data rows: n, energy(keV), counts, rate(1/s)
            parts = line.split()
            if len(parts) < 4:
                continue

            try:
                energy_keV = float(parts[1])
                count = int(parts[2])
            except ValueError:
                continue

            energies.append(energy_keV)
            counts.append(count)

    if not energies or not counts:
        raise ValueError("No channel data found. Check file format or section markers.")

    return energies, counts


def main():
    # Resolve input file
    if len(sys.argv) > 1:
        input_path = Path(sys.argv[1]).expanduser().resolve()
    else:
        # Default to the sample file in the same directory as this script
        input_path = Path(__file__).parent / "Eu-152-16122019.cnf.txt"
        input_path = input_path.resolve()

    if not input_path.exists():
        print(f"Input file not found: {input_path}")
        sys.exit(1)

    energies, counts = parse_cnf_txt(input_path)
    S = []
    F = []
    countS = []
    for i in range(1, len(energies) - 1):
        S.append(counts[i + 1] - 2 * counts[i] + counts[i - 1])
        F.append(math.sqrt(counts[i + 1] + 4 * counts[i] + counts[i - 1]))
    fig, axes = plt.subplots(3, 1, figsize=(10, 8))
    # Plot energy vs count
    axes[0].plot(energies, counts, color="C0", linewidth=1)
    axes[0].set_title("Counts vs Energy")
    axes[0].set_xlabel("Energy (keV)")
    axes[0].set_ylabel("Counts")
    axes[0].grid(True, alpha=0.3)

    # Plot S vs count (align counts with the central index of the second difference)
    count_mid = energies[1:-1]
    axes[1].plot(count_mid, S, color="C1", linewidth=1)
    axes[1].set_title("Counts vs S")
    axes[1].set_xlabel("S (second difference of energy)")
    axes[1].set_ylabel("Counts")
    axes[1].grid(True, alpha=0.3)

    # Plot F vs energy (aligned with the central index)
    axes[2].plot(count_mid, F, color="C2", linewidth=1)
    axes[2].set_title("F vs Energy")
    axes[2].set_xlabel("Energy (keV)")
    axes[2].set_ylabel("F")
    axes[2].grid(True, alpha=0.3)

    plt.tight_layout()
    plt.show()
if __name__ == "__main__":
    main()