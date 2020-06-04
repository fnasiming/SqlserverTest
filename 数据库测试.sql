

--if exists (select * from sys.databases where name = �����ݿ�����)  
 -- drop database [���ݿ���]  if exists (select * from sys.databases where name = �����ݿ�����)
 -- drop database [���ݿ���]



--����
USE [test]
GO

/****** Object:  Table [dbo].[TestTable]    Script Date: 06/03/2020 14:44:15 ******/
SET ANSI_NULLS ON
GO

SET QUOTED_IDENTIFIER ON
GO

if not exists (select * from sysobjects where id = object_id(N'[dbo].[TestTable]') and OBJECTPROPERTY(ID, N'IsUserTable') = 1)  --�жϱ��Ƿ����
CREATE TABLE [dbo].[TestTable](
	[id] [int] NOT NULL,
	[gold] [bigint] NOT NULL,
	[age] [int] NOT NULL,
	[bChild] [tinyint] NOT NULL,
	[name] [nvarchar](50) NOT NULL,
	[interest] [nvarchar](50) NOT NULL
) ON [PRIMARY]

GO



----------------------------------------------------------------------------------------------------
--���洢����
USE [test]
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[GSP_GS_SaveTestData]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)--�жϴ������Ƿ����
DROP PROCEDURE [dbo].GSP_GS_SaveTestData
GO

IF EXISTS (SELECT * FROM DBO.SYSOBJECTS WHERE ID = OBJECT_ID(N'[dbo].[GSP_GS_SelectTestData]') and OBJECTPROPERTY(ID, N'IsProcedure') = 1)
DROP PROCEDURE [dbo].GSP_GS_SelectTestData
GO


SET QUOTED_IDENTIFIER ON 
GO

SET ANSI_NULLS ON 
GO


----------------------------------------------------------------------------------------------------

-- ��������
CREATE  PROCEDURE dbo.GSP_GS_SaveTestData
	@Id				int,
	@gold			bigint,
	@age			int,	
	@bChild			tinyint,
	@name			nvarchar(50),
	@interest		nvarchar(50)
WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ִ���߼�
BEGIN

	INSERT INTO TestTable (id, gold, age,bChild,name,interest)
	VALUES (@Id,@gold, @age,@bChild, @name,@interest)
END

RETURN 0

GO

----------------------------------------------------------------------------------------------------

-- ȡ������
CREATE  PROCEDURE dbo.GSP_GS_SelectTestData

WITH ENCRYPTION AS

-- ��������
SET NOCOUNT ON

-- ִ���߼�
BEGIN

	SELECT *
	FROM TestTable(NOLOCK)
	
END

RETURN 0

GO
----------------------------------------------------------------------------------------------------

