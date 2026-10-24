private void FindPeak()
        {
            peakPos.Clear();

            if (_S.Count == 0 || _F.Count != _S.Count || _N.Count != _S.Count)
                return;

            int radius = _z * _m + 1;

            int minNegWidth = Math.Max(1, radius / 2);
            int maxNegWidth = Math.Max(minNegWidth + 2, 4 * radius);
            double sigmaThreshold = 2.5;
            int refineHalfWindow = Math.Max(2, radius);
            int mergeDistance = Math.Max(2, radius / 2);

            List<int> candidates = new List<int>();

            int i = 1;
            while (i < _S.Count - 1)
            {
                // Candidate region: significantly negative second-difference
                if (_S[i] < -sigmaThreshold * _F[i])
                {
                    int start = i;
                    int minIndex = i;
                    double minValue = _S[i];

                    while (i < _S.Count - 1 && _S[i] < 0.0)
                    {
                        if (_S[i] < minValue)
                        {
                            minValue = _S[i];
                            minIndex = i;
                        }
                        i++;
                    }

                    int end = i - 1;
                    int negWidth = end - start + 1;

                    if (negWidth >= minNegWidth && negWidth <= maxNegWidth)
                    {
                        // Refine on original spectrum: choose local maximum near minIndex
                        int left = Math.Max(0, minIndex - refineHalfWindow);
                        int right = Math.Min(_N.Count - 1, minIndex + refineHalfWindow);

                        int peakIndex = left;
                        int peakCount = _N[left];

                        for (int k = left + 1; k <= right; k++)
                        {
                            if (_N[k] > peakCount)
                            {
                                peakCount = _N[k];
                                peakIndex = k;
                            }
                        }

                        candidates.Add(peakIndex);
                    }
                }
                else
                {
                    i++;
                }
            }

            // Merge peaks too close to each other
            candidates.Sort();
            foreach (int p in candidates)
            {
                if (peakPos.Count == 0)
                {
                    peakPos.Add(p);
                    continue;
                }

                int last = peakPos[peakPos.Count - 1];
                if (Math.Abs(p - last) <= mergeDistance)
                {
                    if (_N[p] > _N[last])
                        peakPos[peakPos.Count - 1] = p;
                }
                else
                {
                    peakPos.Add(p);
                }
            }
        }