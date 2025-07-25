
#download(period='1mo', interval='1d', start=None, end=None, prepost=False, actions=True, auto_adjust=True, 
# repair=False, proxy=<object object>, threads=True, group_by='column', progress=True, timeout=10, **kwargs)

# ticker_symbol = "AAPL"
# start_date = "2024-01-01"
# end_date = "2024-01-02"
# 
# 
# timeInterval= '1m'
# timePeriod='1d'

# Parameters

def pullCSVData(ticker_symbol, start_date, timeInterval, timePeriod):

    import yfinance as yf
    import os   

    folder_path = "src/tickerData"
    file_name = f"{ticker_symbol}_{start_date}_data.csv"

    # Download the data
    data = yf.download([ticker_symbol], period=timePeriod, interval=timeInterval, start=start_date)

    # Save to CSV
    file_path = os.path.join(folder_path, file_name)
    data.to_csv(file_path)

    print(f"Data saved to: {file_path}")


pullCSVData("AAPL", "2025-07-24", '1m', '1d')
