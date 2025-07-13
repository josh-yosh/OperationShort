import yfinance as yf
import os

#download(period='1mo', interval='1d', start=None, end=None, prepost=False, actions=True, auto_adjust=True, 
# repair=False, proxy=<object object>, threads=True, group_by='column', progress=True, timeout=10, **kwargs)

# Parameters
ticker_symbol = "AAPL"
start_date = "2024-01-01"
end_date = "2024-01-02"
folder_path = "src/tickerData"
file_name = f"{ticker_symbol}_data.csv"
timeInterval= '1m'
timePeriod='1d'


apple = yf.Ticker(ticker_symbol)

# Download the data
data = yf.download([ticker_symbol], period=timePeriod, interval=timeInterval)

# Save to CSV
file_path = os.path.join(folder_path, file_name)
data.to_csv(file_path)

print(f"Data saved to: {file_path}")
