---
created: 2026-03-08T20:10
updated: 2026-03-08T21:11
---
Section 5.3 - Time Series Forecasting Methods

Data often needs to be detrended and smoothed.
- simple moving average
- weighted moving average
- differencing
- regression
- seasonal-trend decomposition using LOESS (STL)

You can use the autocorrelation function to identify the period of seasonal data. Then you can adjust the time series.

### Autoregressive Integrated Moving Average (ARIMA)
This method captures trend and seasonality
- autoregressive model - captures repeated patterns
- integrative component - detrends
- moving average model - predictive model
This works best on a stationary time series.
