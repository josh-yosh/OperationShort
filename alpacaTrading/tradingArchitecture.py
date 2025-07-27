from alpaca.trading.client import TradingClient
from alpaca.trading.requests import GetAssetsRequest
from alpaca.trading.enums import AssetClass
from alpaca.trading.requests import MarketOrderRequest, LimitOrderRequest
from alpaca.trading.enums import OrderSide, TimeInForce
from alpaca.data.live import StockDataStream
import requests


#please do not commit my api keys
# trading_client = TradingClient('api-key', 'secret-key', paper=True)
trading_client = TradingClient('', '', paper=True)
stock_stream = StockDataStream("", "")

async def startDataStream():
    # async handler
    async def quote_data_handler(data):
        # quote data will arrive here
        print(data)

    stock_stream.subscribe_quotes(quote_data_handler, "SPY")

    stock_stream.run()


def getBuyingPower():
    # Get our account information.
    account = trading_client.get_account()

    # Check if our account is restricted from trading.
    if account.trading_blocked:
        print('Account is currently restricted from trading.')

    # Check how much money we can use to open new positions.
    return account.buying_power


def getProfitLoss():
    # Get our account information.
    account = trading_client.get_account()

    # Check our current balance vs. our balance at the last market close
    balance_change = float(account.equity) - float(account.last_equity)

    return balance_change


def getAllAssets():
    # search for US equities
    search_params = GetAssetsRequest(asset_class=AssetClass.US_EQUITY)

    assets = trading_client.get_all_assets(search_params)
    return assets


def isSymbolTradable():
    # search for AAPL
    aapl_asset = trading_client.get_asset('AAPL')

    if aapl_asset.tradable:
        print('We can trade AAPL.')
        return True
    else:
        print('We cannot trade AAPL.')
        return False


def makeMarketOrder(stockSymbol, volume, orderSide, timeInForce):
    # preparing market order
    market_order_data = MarketOrderRequest(
                        symbol=stockSymbol,
                        qty=volume,
                        side=orderSide,
                        time_in_force=timeInForce
                        )
    return market_order_data


#can be used for limit orders too
def sumbitMarketOrder(market_order_data):
    # Market order
    market_order = trading_client.submit_order(
                    order_data=market_order_data
                )
    print("Market Order sent")


def makeLimitOrder(stockSymbol, limitPrice, volume, orderSide, timeInForce):
    # preparing limit order 
    limit_order_data = LimitOrderRequest(
                        symbol=stockSymbol,
                        limit_price=limitPrice,
                        qty = volume,
                        side=orderSide,
                        time_in_force=timeInForce
                    )
    return limit_order_data


def getData():
    url = "https://data.alpaca.markets/v2/stocks/bars?symbols=AAPL&timeframe=1Min&start=2024-01-03T00%3A00%3A00Z&end=2024-01-04T00%3A00%3A00Z&limit=10000&adjustment=raw&feed=sip&sort=asc"

    headers = {
        "accept": "application/json",
        "APCA-API-KEY-ID": "", #fill out
        "APCA-API-SECRET-KEY": "" # fill out
    }

    response = requests.get(url, headers=headers)
    print(response.text)



getBuyingPower()
getProfitLoss()
# getAllAssets()
isSymbolTradable()