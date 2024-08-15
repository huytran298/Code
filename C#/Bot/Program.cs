using Discord;
using Discord.WebSocket;
using System;
using System.Threading.Tasks;
using Discord.Commands;
using Discord.Net;
using Discord.Interactions;


namespace Adivisor
{
public class Program
{
    private DiscordSocketClient _client;
    public static void Main(string[] args) => new Program().MainAsync().GetAwaiter().GetResult();
    private const string token = "MTI3MzU1MTA1Mjc0MTkzNTEzNQ.Gm-99T.HINg4MV4PNyn1ApYpga7ZFu5qAqr3Nx-pyh1c8";

    public async Task MainAsync()
    {
        
        var config = new DiscordSocketConfig()
        {
        // Other config options can be presented here.
        GatewayIntents = GatewayIntents.All
        };

        _client = new DiscordSocketClient(config);
        _client.Log += Log;
        _client.MessageReceived += MessageReceived;
        

        await _client.LoginAsync(TokenType.Bot, token);
        await _client.StartAsync();
        await Task.Delay(-1);

    }
    [Command("spawner")]
    public async Task Spawn()
    {
        Console.WriteLine("read");
    
    }
    private async Task MessageReceived(SocketMessage message)
    {
        if(!message.Author.IsBot){
            if(message.Content == "ping"){
                await message.Channel.SendMessageAsync("pong");
            }
        }

    }

    private Task Log(LogMessage msg)
    {
        Console.WriteLine(msg.ToString());
        return Task.CompletedTask;
    }

   }
}